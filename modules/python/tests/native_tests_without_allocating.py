#!/usr/bin/env python3
import MiniQbtNative
import unittest

class NativeTests(unittest.TestCase):
    faultyReference = "[MiniQbt Async reference]", 99999

    def test_use_get_register_without_allocating(self):
        try:
            MiniQbtNative.qasm_async_intepreter_get_registers(NativeTests.faultyReference)
            
        except MiniQbtNative.error as err:
            return
        
        raise Exception("Should fail")

    def test_use_intepret_without_allocating(self):
        try:
            MiniQbtNative.async_intepret(NativeTests.faultyReference, "creg a[1]; qreg b[1];")
        except MiniQbtNative.error as err:
            return
        
        raise Exception("Should fail")
        
    def test_use_intepreter_has_errors_without_allocating(self):
        try:
            MiniQbtNative.qasm_async_intepreter_has_errors(NativeTests.faultyReference)
        except MiniQbtNative.error as err:
            return
        
        raise Exception("Should fail")

    def test_destroy_qasm_async_intepreter_without_allocating(self):
        try:
            MiniQbtNative.destroy_qasm_async_intepreter(NativeTests.faultyReference)
        except MiniQbtNative.error as err:
            return
        
        raise Exception("Should fail")


if __name__ == '__main__':
    unittest.main()