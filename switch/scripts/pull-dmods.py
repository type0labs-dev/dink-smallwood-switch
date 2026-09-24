#!/usr/bin/env python3
"""Pull DMOD addons from Nintendo Switch FTP to local bin/dmods/."""
import argparse
import ftplib
import os
from pathlib import Path
import sys
import time

ROOT = Path(__file__).resolve().parents[2]
DEST_DIR = ROOT / 'bin/dmods'


def parse_list(ftp):
    lines = []
    ftp.retrlines('LIST', lines.append)
    dirs = []
    files = []
    for line in lines:
        parts = line.split(None, 8)
        if len(parts) < 9:
            continue
        flags = parts[0]
        size = int(parts[4])
        name = parts[8]
        if name in ('.', '..'):
            continue
        if flags.startswith('d'):
            dirs.append(name)
        else:
            files.append((name, size))
    return dirs, files


def download_recursive(ftp, remote_dir, local_dir, stats):
    local_dir.mkdir(parents=True, exist_ok=True)
    dirs, files = parse_list(ftp)
    for name, size in files:
        dest_path = local_dir / name
        if dest_path.is_file() and dest_path.stat().st_size == size:
            stats['skipped'] += 1
            stats['bytes'] += size
            continue
        with open(dest_path, 'wb') as fp:
            ftp.retrbinary(f'RETR {name}', fp.write, blocksize=65536)
        stats['downloaded'] += 1
        stats['bytes'] += size

    for d in dirs:
        ftp.cwd(d)
        download_recursive(ftp, f'{remote_dir}/{d}', local_dir / d, stats)
        ftp.cwd('..')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--host', default='10.13.99.120')
    parser.add_argument('--port', type=int, default=5000)
    parser.add_argument('--dmod', help='Only pull specific DMOD')
    args = parser.parse_args()

    DEST_DIR.mkdir(parents=True, exist_ok=True)
    print(f'Connecting to {args.host}:{args.port}...')
    with ftplib.FTP() as ftp:
        ftp.connect(args.host, args.port, timeout=30)
        ftp.login('anonymous', '')
        ftp.cwd('/switch/dink-smallwood/dmods')
        dmods = ftp.nlst()
        if args.dmod:
            if args.dmod not in dmods:
                print(f'DMOD {args.dmod} not found on Switch. Available: {dmods}')
                return 1
            dmods = [args.dmod]

        total_dmods = len(dmods)
        print(f'Found {total_dmods} DMOD(s) on Switch: {", ".join(dmods)}')
        start_time = time.time()
        grand_stats = {'downloaded': 0, 'skipped': 0, 'bytes': 0}

        for idx, dmod in enumerate(dmods, 1):
            dmod_start = time.time()
            stats = {'downloaded': 0, 'skipped': 0, 'bytes': 0}
            ftp.cwd(dmod)
            download_recursive(ftp, f'/switch/dink-smallwood/dmods/{dmod}', DEST_DIR / dmod, stats)
            ftp.cwd('..')
            duration = time.time() - dmod_start
            mb = stats['bytes'] / (1024 * 1024)
            print(f'[{idx}/{total_dmods}] {dmod:15} -> {stats["downloaded"]} dl, {stats["skipped"]} cached, {mb:.2f} MB in {duration:.1f}s')
            for k in grand_stats:
                grand_stats[k] += stats[k]

        total_duration = time.time() - start_time
        total_mb = grand_stats['bytes'] / (1024 * 1024)
        print('-' * 60)
        print(f'Complete: {grand_stats["downloaded"]} downloaded, {grand_stats["skipped"]} cached ({total_mb:.2f} MB) in {total_duration:.1f}s')
        print(f'Saved to: {DEST_DIR}')


if __name__ == '__main__':
    sys.exit(main() or 0)
