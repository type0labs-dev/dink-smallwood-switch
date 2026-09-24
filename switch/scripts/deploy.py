#!/usr/bin/env python3
"""Upload only the staged Dink tree. Publish the NRO last, verifying readback."""
import argparse
import ftplib
import hashlib
import io
import json
from datetime import datetime, timezone
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[2]
REMOTE = '/switch/dink-smallwood'


def checked_path(name):
    path = PurePosixPath(name)
    if path.is_absolute() or '..' in path.parts or not path.parts:
        raise ValueError(f'Unsafe manifest path: {name}')
    return path


def publish_verified(ftp, temporary, target):
    """Publish an already verified upload, including on FTP servers without replace."""
    try:
        exists = ftp.size(target) is not None
    except ftplib.error_perm as error:
        if not str(error).startswith('550'):
            raise
        exists = False
    backup = None
    if exists:
        stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
        backup = target + f'.bak-{stamp}'
        ftp.rename(target, backup)
    try:
        ftp.rename(temporary, target)
    except Exception:
        if backup:
            ftp.rename(backup, target)
        raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--host', required=True)
    parser.add_argument('--port', type=int, default=5000)
    args = parser.parse_args()
    stage = ROOT / 'dist-switch/switch/dink-smallwood'
    manifest_bytes = (stage / 'manifest.json').read_bytes()
    manifest = json.loads(manifest_bytes)['files']
    for name, info in manifest.items():
        path = stage.joinpath(*checked_path(name).parts)
        data = path.read_bytes()
        if len(data) != info['size'] or hashlib.sha256(data).hexdigest() != info['sha256']:
            raise ValueError(f'Staging changed since packaging: {name}')
    with ftplib.FTP() as ftp:
        ftp.connect(args.host, args.port, timeout=30)
        ftp.login('anonymous', '')
        ftp.voidcmd('TYPE I')
        made = set()

        def mkdir(directory):
            if directory in made:
                return
            try:
                ftp.mkd(directory)
            except ftplib.error_perm:
                # A permission error is not necessarily "already exists".
                ftp.cwd(directory)
                ftp.cwd('/')
            made.add(directory)

        mkdir('/switch')
        mkdir(REMOTE)
        previous = {}
        old = io.BytesIO()
        try:
            ftp.retrbinary(f'RETR {REMOTE}/manifest.json', old.write)
            previous = json.loads(old.getvalue()).get('files', {})
        except (ftplib.error_perm, ValueError):
            pass

        def upload(name, data):
            target = f'{REMOTE}/{name}'
            parent = PurePosixPath(target).parent
            for directory in reversed([parent, *parent.parents]):
                if str(directory) != '/':
                    mkdir(str(directory))
            temporary = target + '.uploading'
            ftp.storbinary(f'STOR {temporary}', io.BytesIO(data), blocksize=128*1024)
            digest = hashlib.sha256()
            ftp.retrbinary(f'RETR {temporary}', digest.update, blocksize=128*1024)
            if digest.hexdigest() != hashlib.sha256(data).hexdigest():
                raise RuntimeError(f'FTP readback mismatch: {name}')
            publish_verified(ftp, temporary, target)

        # The executable only becomes visible after all of its assets are verified.
        names = sorted(manifest, key=lambda name: (name.endswith('.nro'), name))
        transferred = skipped = 0
        for i, name in enumerate(names, 1):
            info = manifest[name]
            if previous.get(name) == info:
                try:
                    if ftp.size(f'{REMOTE}/{name}') == info['size']:
                        skipped += 1
                        continue
                except ftplib.error_perm:
                    pass
            upload(name, stage.joinpath(*checked_path(name).parts).read_bytes())
            transferred += 1
            if transferred % 50 == 0 or name.endswith('.nro'):
                print(f'{i}/{len(names)} verified: {name}', flush=True)
        upload('manifest.json', manifest_bytes)
        print(f'FTP complete: {transferred} uploaded and verified, {skipped} unchanged. {REMOTE}')


if __name__ == '__main__':
    main()
