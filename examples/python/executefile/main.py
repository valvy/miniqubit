#!/usr/bin/env python
from PyMiniQbt import getVersion, getName, QasmAsyncInterpreter

import sys


def main(arguments):
    if(not len(arguments) == 2):
        print("which file?")
        sys.exit(-1)

    print("Using", getName(), "version:", getVersion())
    with open(arguments[1]) as dat:
        src = dat.read()
        interpreter = QasmAsyncInterpreter()
        interpreter.interpret(src)
        while interpreter.hasErrors():
            print(interpreter.getError())
        
        print("results:")
        for register in interpreter.getRegisters():
            print(register,":",interpreter.readClassicResult(register).dataToString())
        



if __name__ == "__main__":
    main(sys.argv)