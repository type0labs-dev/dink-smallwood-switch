#!/usr/bin/env python3
"""Fetch the pinned, redistributable GUS bank used by Switch SDL_mixer/TiMidity."""
import hashlib
import io
from pathlib import Path
import tarfile
import urllib.request

ROOT = Path(__file__).resolve().parents[2]
URL = 'https://deb.debian.org/debian/pool/main/f/freepats/freepats_20060219.orig.tar.gz'
SHA256 = '70bf8ca084df3903d6c9de43fe20539fc0a553d95cfba4d525da3fe66fda5f10'


def main():
    cache = ROOT / 'build-switch/downloads/freepats_20060219.orig.tar.gz'
    if not cache.exists():
        cache.parent.mkdir(parents=True, exist_ok=True)
        with urllib.request.urlopen(URL, timeout=60) as response:
            data = response.read()
        if hashlib.sha256(data).hexdigest() != SHA256:
            raise SystemExit('FreePats checksum mismatch; refusing to use it.')
        cache.write_bytes(data)
    data = cache.read_bytes()
    if hashlib.sha256(data).hexdigest() != SHA256:
        raise SystemExit('Cached FreePats checksum mismatch.')
    with tarfile.open(fileobj=io.BytesIO(data), mode='r:gz') as outer:
        nested = outer.extractfile('freepats-20060219/upstream/freepats-20060219.tar.bz2').read()
    target = ROOT / 'bin/dink/midi/freepats'
    target.mkdir(parents=True, exist_ok=True)
    # Copy only regular members below the known archive root; never follow links.
    with tarfile.open(fileobj=io.BytesIO(nested), mode='r:bz2') as archive:
        for member in archive.getmembers():
            if not member.isfile():
                continue
            rel = Path(member.name)
            if rel.is_absolute() or '..' in rel.parts or rel.parts[0] != 'freepats':
                raise SystemExit('Unexpected FreePats archive path.')
            dest = target / Path(*rel.parts[1:])
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(archive.extractfile(member).read())
    # crude.cfg is the upstream mapping with substitutes for unavailable programs.
    # Relative paths work with the fixed game cwd and in the host regression test.
    (target / 'timidity.cfg').write_text(
        '# Switch configuration; original FreePats samples/configs are unmodified.\n'
        'dir dink/midi/freepats\nsource crude.cfg\n')
    (target / 'SOURCE.txt').write_text(f'FreePats 20060219\n{URL}\nSHA256 {SHA256}\n'
        'See README and COPYING for GPL-2.0-or-later with composition exception.\n'
        'crude.cfg supplies substitute instruments for incomplete GM coverage.\n')
    print(f'Prepared FreePats MIDI instruments: {target}')


if __name__ == '__main__':
    main()
