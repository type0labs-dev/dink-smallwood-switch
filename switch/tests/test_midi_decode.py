import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MidiDecodeTests(unittest.TestCase):
    def test_original_midi_tracks_produce_audio_with_packaged_bank(self):
        source = Path(os.environ.get('DINK_SDL_MIXER_SOURCE',
                      str(ROOT / 'build-switch/music-research/SDL2_mixer-2.0.4')))
        if not (source / 'timidity/timidity.c').exists():
            self.skipTest('Provide SDL2_mixer 2.0.4 source via DINK_SDL_MIXER_SOURCE')
        config = 'dink/midi/freepats/timidity.cfg'
        self.assertTrue((ROOT / 'bin' / config).is_file(), 'Run prepare-music.py first')
        bank = ROOT / 'bin/dink/midi/freepats'
        # Validate every instrument path in the upstream substitute mapping.
        for line in (bank / 'crude.cfg').read_text().splitlines():
            fields = line.split()
            if fields and fields[0].isdigit():
                self.assertTrue((bank / fields[1]).is_file(), fields[1])
        flags = shlex.split(subprocess.check_output(
            ['pkg-config', '--cflags', '--libs', 'sdl2'], text=True))
        with tempfile.TemporaryDirectory() as tmp:
            exe = Path(tmp) / 'midi'
            files = sorted((source / 'timidity').glob('*.c'))
            subprocess.run(['cc', '-std=c99', '-O2', '-I', str(source / 'timidity'),
                            str(ROOT / 'switch/tests/midi_decode.c'),
                            *map(str, files), *flags, '-lm', '-o', str(exe)], check=True)
            # On a host with a system TiMidity config the old failure cannot be isolated.
            if not any(Path(p).exists() for p in ['/etc/timidity.cfg', '/etc/timidity/freepats.cfg']):
                subprocess.run([str(exe), 'missing.cfg'], cwd=tmp, check=True)
            midis = sorted((ROOT / 'bin/dink/sound').glob('*.mid'))
            self.assertEqual(len(midis), 33)
            subprocess.run([str(exe), config, *map(str, midis)], cwd=ROOT / 'bin', check=True)
