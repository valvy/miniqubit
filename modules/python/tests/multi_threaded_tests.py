#!/usr/bin/env python3
from MiniQbt.Intepreter import QasmAsyncIntepreter
import unittest
import threading

class NativeTests(unittest.TestCase):

    def thread(self):
        
        for x in range(0, 200):
            x = QasmAsyncIntepreter()
            x.intepret("qreg q[1]; creg c[1]; x q; measure q -> c;")
            self.assertFalse(x.hasErrors())
            for register in x.getRegisters():
                self.assertEqual(x.readClassicRegister(register), '1')

    def test_single_thread(self):
        self.thread()


    def activate_multiple_threads(self, amount = 2):
        dat = []
        for i in range(0, amount):
            dat.append(threading.Thread(target=self.thread))
        
        for i in dat:
            i.start()

        for i in dat:
            i.join()


    def test_double_thread(self):
        self.activate_multiple_threads(2)

    def test_ten_threads(self):
        self.activate_multiple_threads(10)

    def test_twenty_threads(self):
        self.activate_multiple_threads(20)

    


if __name__ == '__main__':
    unittest.main()
