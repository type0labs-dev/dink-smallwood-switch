"""Compile and exercise the same record reader used by the Switch engine."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MapRecordReaderTest(unittest.TestCase):
    def test_reader_against_original_maps_and_stream_failures(self):
        compiler = shutil.which("g++")
        if not compiler:
            self.skipTest("g++ is required for the native map reader test")
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "map-record-reader"
            subprocess.run([
                compiler, "-std=c++11", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=address,undefined", "-g", "-I", str(ROOT),
                str(ROOT / "switch/tests/map_record_reader.cpp"),
                "-o", str(executable),
            ], check=True)
            subprocess.run([str(executable), str(ROOT / "bin/dink/map.dat")], check=True)


if __name__ == "__main__":
    unittest.main()
