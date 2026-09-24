from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class PathCacheTests(unittest.TestCase):
    def test_path_cache_behavior(self):
        with tempfile.TemporaryDirectory() as tmp:
            binary = Path(tmp) / 'test-path-cache'
            subprocess.run([
                'g++', '-std=c++11', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=address,undefined', '-g', '-I', str(ROOT),
                str(ROOT / 'switch/tests/path_cache.cpp'), '-o', str(binary)
            ], check=True)
            subprocess.run([str(binary)], check=True)


if __name__ == '__main__':
    unittest.main()
