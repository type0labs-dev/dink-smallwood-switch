from pathlib import Path
import os
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[2]
class GPUCaptureTests(unittest.TestCase):
    def test_actual_capture_method_matches_legacy_pixels(self):
        source=(ROOT/'proton/shared/Renderer/Surface.cpp').read_text()
        start=source.index('void Surface::CopyFromScreen()')
        method=source[start:source.index('//used in debugging',start)]
        legacy=method.replace('Surface::CopyFromScreen()', 'Surface::CopyFromScreenLegacy()').replace('#ifdef __SWITCH__','#if 0')
        with tempfile.TemporaryDirectory() as tmp:
            Path(tmp,'surface_capture.inc').write_text(method+'\n'+legacy)
            binary=Path(tmp,'capture')
            subprocess.run(['g++','-std=c++11','-D__SWITCH__','-Wall','-Wextra','-Werror','-I',tmp,
                str(ROOT/'switch/tests/gpu_capture.cpp'),'-lEGL','-lGLESv2','-o',str(binary)],check=True)
            env=dict(os.environ,EGL_PLATFORM='surfaceless',LIBGL_ALWAYS_SOFTWARE='1')
            subprocess.run([str(binary)],check=True,env=env)
