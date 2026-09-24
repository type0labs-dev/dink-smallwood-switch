import importlib.util
import ftplib
import io
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

SCRIPTS = Path(__file__).resolve().parents[1] / 'scripts'


def module(name):
    spec = importlib.util.spec_from_file_location(name, SCRIPTS / f'{name}.py')
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


package = module('package')
deploy = module('deploy')


class NonReplacingFTP:
    def __init__(self, fail_publish=False):
        self.files = {'manifest.json': b'old', 'manifest.json.uploading': b'new',
                      'dink/autosave.dat': b'progress'}
        self.fail_publish = fail_publish

    def size(self, name):
        if name not in self.files:
            raise ftplib.error_perm('550 File not found')
        return len(self.files[name])

    def rename(self, source, target):
        if target in self.files:
            raise ftplib.error_perm('553 File exists')
        if self.fail_publish and source.endswith('.uploading'):
            raise ftplib.error_temp('450 Rename failed')
        self.files[target] = self.files.pop(source)


class DeliveryTests(unittest.TestCase):
    def test_manifest_update_on_server_without_overwrite_keeps_backup_and_save(self):
        ftp = NonReplacingFTP()
        deploy.publish_verified(ftp, 'manifest.json.uploading', 'manifest.json')
        self.assertEqual(ftp.files['manifest.json'], b'new')
        self.assertEqual(ftp.files['dink/autosave.dat'], b'progress')
        backups = [data for name, data in ftp.files.items() if '.bak-' in name]
        self.assertEqual(backups, [b'old'])

    def test_failed_publication_restores_previous_file(self):
        ftp = NonReplacingFTP(fail_publish=True)
        with self.assertRaises(ftplib.error_temp):
            deploy.publish_verified(ftp, 'manifest.json.uploading', 'manifest.json')
        self.assertEqual(ftp.files['manifest.json'], b'old')
        self.assertEqual(ftp.files['manifest.json.uploading'], b'new')
        self.assertEqual(ftp.files['dink/autosave.dat'], b'progress')

    def test_package_excludes_progress_and_records_asset_hashes(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for name in ('bin/dink', 'bin/interface', 'bin/audio', 'proton', 'build-switch'):
                (root / name).mkdir(parents=True)
            for name in ('save1.dat', 'SAVE10.DAT', 'quicksave.dat', 'autosavedb.dat', 'continue_state.dat', 'save1.dat.bak', 'save1.dat.pending', '.dink-save.txn', 'music-diagnostic.flag', 'music-diagnostic.txt', 'music-recovery.txt'):
                (root / 'bin/dink' / name).write_bytes(b'personal progress')
            (root / 'bin/dink/map.dat').write_bytes(b'game data')
            (root / 'LICENSE.md').write_text('license')
            (root / 'proton/LICENSE.md').write_text('license')
            nro = bytearray(128)
            nro[16:20] = b'NRO0'
            struct.pack_into('<I', nro, 24, len(nro))
            (root / 'build-switch/DinkSmallwood.nro').write_bytes(nro)
            with patch.object(package, 'ROOT', root), patch('sys.stdout', new=io.StringIO()):
                package.main()
            stage = root / 'dist-switch/switch/dink-smallwood'
            names = json.loads((stage / 'manifest.json').read_text())['files']
            self.assertEqual(set(names), {'DinkSmallwood.nro', 'dink/map.dat', 'LICENSE-Dink.txt', 'LICENSE-Proton.txt'})
            self.assertEqual(names['dink/map.dat']['size'], 9)
            self.assertTrue((root / 'bin/dink/save1.dat').exists())

    def test_invalid_nro_does_not_replace_previous_package(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'build-switch').mkdir()
            (root / 'build-switch/DinkSmallwood.nro').write_bytes(b'not executable')
            stage = root / 'dist-switch/switch/dink-smallwood'
            stage.mkdir(parents=True)
            (stage / 'sentinel').write_text('previous package')
            with patch.object(package, 'ROOT', root), self.assertRaises(SystemExit):
                package.main()
            self.assertTrue((stage / 'sentinel').exists())

    def test_missing_midi_bank_does_not_replace_previous_package(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'build-switch').mkdir()
            nro = bytearray(128)
            nro[16:20] = b'NRO0'
            struct.pack_into('<I', nro, 24, len(nro))
            (root / 'build-switch/DinkSmallwood.nro').write_bytes(nro)
            sound = root / 'bin/dink/sound'
            sound.mkdir(parents=True)
            (sound / '1.mid').write_bytes(b'MThd')
            stage = root / 'dist-switch/switch/dink-smallwood'
            stage.mkdir(parents=True)
            (stage / 'sentinel').write_text('previous package')
            with patch.object(package, 'ROOT', root), self.assertRaisesRegex(SystemExit, 'MIDI instruments'):
                package.main()
            self.assertTrue((stage / 'sentinel').exists())

    def test_manifest_cannot_escape_remote_game_directory(self):
        for name in ('../atmosphere/config.ini', '/switch/gamevault/GameVault.nro', 'dink/../../save.dat', ''):
            with self.subTest(name=name), self.assertRaises(ValueError):
                deploy.checked_path(name)
        self.assertEqual(str(deploy.checked_path('dink/story/start.c')), 'dink/story/start.c')


if __name__ == '__main__':
    unittest.main()
