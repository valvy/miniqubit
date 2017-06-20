#!/usr/bin/env python3
from MiniQbt.Interpreter import QasmAsyncInterpreter
import unittest

class AbuseQasmEmulator(unittest.TestCase):
    def test_output_with_geterror_on_no_error(self):
         x = QasmAsyncInterpreter()
         if(not x.getError() == "No error"):
            raise "Invalid input"





if __name__ == '__main__':
    unittest.main()