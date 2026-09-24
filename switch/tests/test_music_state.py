from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MusicStateTests(unittest.TestCase):
    def test_playback_failure_preserves_track_and_recovery_respects_silence(self):
        text = (ROOT / 'source/dink/dink.cpp').read_text()
        def function(signature):
            start = text.index(signature + '\n{')
            end = text.index('\n}\n', start) + 3
            return text[start:end]
        code = '\n'.join(function(s) for s in [
            'bool PlayMidi(const char *sFileName)', 'bool StopMidi()', 'bool SaveSoundState(FILE *fp)',
            'static string GetLocalMusicRecoveryTrack()', 'bool LoadSoundState(FILE *fp)'])
        code += function('static void RecoverMusicAfterLoad()')
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            (tmp / 'music_functions.inc').write_text(code)
            exe = tmp / 'music_state'
            subprocess.run(['g++', '-std=c++14', '-D__SWITCH__', '-fsanitize=address,undefined',
                            '-fno-omit-frame-pointer', '-g', '-I', str(ROOT / 'switch'),
                            '-I', str(tmp), str(ROOT / 'switch/tests/music_state.cpp'),
                            '-o', str(exe)], check=True)
            subprocess.run([str(exe)], cwd=tmp, check=True)
