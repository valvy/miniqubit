#!/usr/bin/env python3
from PyMiniQbt import QasmAsyncIntepreter
import unittest
import native_tests


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromModule(native_tests)
    unittest.TextTestRunner(verbosity=2).run(suite)

