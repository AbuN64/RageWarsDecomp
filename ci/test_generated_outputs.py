"""The real public Makefile refuses missing inputs before invoking tool seams."""
import pathlib
import shutil
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
VERSIONS = ('de', 'eu', 'eu-x', 'us', 'us-rev1')
REQUIRED = ['RageWars.ld'] + [f'versions/{v}/{name}' for v in VERSIONS
                            for name in ('text_sizes.mk', 'splat.yaml')]
# A real FSPLIT assignment emitted for the barrel unit; only its renamed path changes.
FSPLIT = 'build/us/Source/Ai/barrel_getfacingside.cpp.o: FSPLIT := fsplit\n'

class GeneratedInputs(unittest.TestCase):
    def setUp(self):
        scratch = ROOT / '.tmp'
        scratch.mkdir(exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=scratch)
        self.addCleanup(self.tmp.cleanup)
        self.root = pathlib.Path(self.tmp.name)
        for name in ('Makefile', 'layout.mk', '.gitignore'):
            shutil.copyfile(ROOT / name, self.root / name)
        header = self.root / 'Include/include_asm.h'
        header.parent.mkdir()
        header.write_text('/* authored header seam */\n')
        for name in REQUIRED:
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(FSPLIT if name.endswith('text_sizes.mk') else '# generated fixture\n')

    def make(self, *args):
        return subprocess.run(['make', 'CHECK=tree', *args], cwd=self.root,
                              text=True, capture_output=True)

    def test_each_missing_input_refuses_before_normal_or_nmraw_build(self):
        self.assertEqual(self.make('check').returncode, 0)
        for name in REQUIRED:
            with self.subTest(path=name):
                path = self.root / name
                data = path.read_bytes()
                path.unlink()
                for goal in ('check', 'build/nmraw/us/Source/Ai/barrel_getfacingside.cpp.o'):
                    result = self.make(goal)
                    self.assertNotEqual(result.returncode, 0)
                    self.assertIn(name + ' is missing', result.stderr)
                path.write_bytes(data)
                result = self.make('check')
                self.assertEqual(result.returncode, 0, result.stderr)

    def test_checkout_preserves_untracked_real_fsplit_rows(self):
        def git(*args):
            return subprocess.run(['git', *args], cwd=self.root, check=True,
                                  text=True, capture_output=True).stdout
        git('init', '-q')
        git('add', 'Makefile', 'layout.mk', '.gitignore', 'Include/include_asm.h')
        git('-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid',
            'commit', '-qm', 'Create authored fixture')
        before = {name: (self.root / name).read_bytes() for name in REQUIRED}
        git('checkout', 'HEAD', '--', '.')
        self.assertEqual(before, {name: (self.root / name).read_bytes() for name in REQUIRED})
        for name in REQUIRED:
            git('check-ignore', '-q', '--', name)
        self.assertIn(b'FSPLIT := fsplit', before['versions/us/text_sizes.mk'])
        self.assertEqual(self.make('check').returncode, 0)

if __name__ == '__main__':
    unittest.main()
