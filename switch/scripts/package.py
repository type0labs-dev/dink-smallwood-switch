#!/usr/bin/env python3
"""Stage a clean, community-ready Switch build of Dink Smallwood HD: Edição Definitiva PT-BR."""
import fnmatch
import hashlib
import json
import shutil
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXCLUDED = ('save*.dat*', 'quicksave*', 'autosave*', 'continue_state*', '.dink-save.txn*', 'log.txt', 'music-diagnostic.*', 'music-recovery.txt')

def is_excluded(path):
    if any(fnmatch.fnmatch(path.name.lower(), pattern) for pattern in EXCLUDED):
        return True
    # Exclude raw flare creature BMPs from base game package (kept in research/web_assets)
    if 'graphics/foes/flare_' in path.as_posix():
        return True
    return False

def main():
    nro = ROOT / 'build-switch/DinkSmallwood.nro'
    if not nro.exists():
        raise SystemExit(f'Missing NRO: {nro}')
    data = nro.read_bytes()
    if data[16:20] != b'NRO0' or struct.unpack_from('<I', data, 24)[0] > len(data):
        raise SystemExit('Invalid NRO; refusing to package.')
    if any((ROOT / 'bin/dink/sound').glob('*.mid')):
        if not (ROOT / 'bin/dink/midi/freepats/timidity.cfg').is_file():
            raise SystemExit('MIDI instruments missing; run python3 switch/scripts/prepare-music.py first.')

    stage = ROOT / 'dist-switch/switch/dink-smallwood'
    if stage.exists():
        shutil.rmtree(stage)
    stage.mkdir(parents=True)

    for name in ('dink', 'interface', 'audio'):
        source = ROOT / 'bin' / name
        if not source.is_dir():
            raise SystemExit(f'Missing assets: {source}')
        for path in sorted(source.rglob('*')):
            if path.is_file() and not is_excluded(path):
                target = stage / name / path.relative_to(source)
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(path, target)

    shutil.copyfile(nro, stage / nro.name)
    shutil.copyfile(ROOT / 'LICENSE.md', stage / 'LICENSE-Dink.txt')
    shutil.copyfile(ROOT / 'proton/LICENSE.md', stage / 'LICENSE-Proton.txt')

    files = {
        path.relative_to(stage).as_posix(): {
            'size': path.stat().st_size,
            'sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
        }
        for path in sorted(stage.rglob('*')) if path.is_file()
    }
    (stage / 'manifest.json').write_text(json.dumps({'version': 1, 'files': files}, indent=2)+'\n')
    print(f'Packaged {len(files)} files, {sum(f["size"] for f in files.values()):,} bytes: {stage}')

if __name__ == '__main__':
    main()
