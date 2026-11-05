import contextlib,io,runpy,sys,unittest
from unittest.mock import patch,mock_open
from pathlib import Path
SCRIPT=str(Path(__file__).with_name('slots.py'))
LD=''' .one 0x80000000 : AT(0x100)
 {
 Source/Ui/example.cpp.o(.data);
 . = 0x4;
 Source/Ui/example.cpp.o(.data);
 . = 0x8;
 Source/Ui/tail.cpp.o(.data);
 }
 .two 0x80000100 : AT(0x110)
 {
 }
'''
class Census(unittest.TestCase):
 def run_script(self,exists):
  out,err=io.StringIO(),io.StringIO()
  with patch('builtins.open',mock_open(read_data=LD)),patch.object(Path,'is_file',return_value=exists),patch('subprocess.run') as proc,patch.object(sys,'argv',[SCRIPT,'us']),contextlib.redirect_stdout(out),contextlib.redirect_stderr(err):
   proc.return_value.stdout=' 0 .data 0000000c\n'
   try: runpy.run_path(SCRIPT);code=0
   except SystemExit as e: code=e.code
  return code,out.getvalue(),err.getvalue()
 def test_missing_object_refuses(self):
  code,out,err=self.run_script(False);self.assertEqual(code,1);self.assertIn('MISSING Source/Ui/example.cpp.o',err);self.assertIn('missing 2',err)
 def test_duplicate_consumed_once_and_tail_checked(self):
  code,out,err=self.run_script(True);self.assertEqual(code,0);self.assertEqual(out.count('OVER'),2);self.assertIn('tail.cpp.o .data size 0xc slot 0x8',out)
if __name__=='__main__':unittest.main()
