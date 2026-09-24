from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
class SaveAndPerformanceTests(unittest.TestCase):
    def test_failures_recovery_cache_and_pacing(self):
        with tempfile.TemporaryDirectory() as tmp:
            binary = Path(tmp) / 'test-save-performance'
            subprocess.run(['g++', '-std=c++11', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=address,undefined', '-g', '-I', str(ROOT),
                str(ROOT/'switch/tests/save_and_performance.cpp'), '-o', str(binary)], check=True)
            subprocess.run([str(binary), tmp], check=True)
