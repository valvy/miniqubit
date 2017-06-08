#!/usr/bin/env python3
from MiniQbt.Globals import getVersion, getName
from MiniQbt.Intepreter import QasmAsyncIntepreter
import sys


def main(arguments):
    if(not len(arguments) == 2):
        print("which file?")
        sys.exit(-1)

    print("Using", getName(), "version:", getVersion())
    with open(arguments[1]) as dat:
        src = dat.read()
        intepreter = QasmAsyncIntepreter()
        intepreter.intepret(src)
        while intepreter.hasErrors():
            print(intepreter.getError())
        
        print("results:")
        for register in intepreter.getRegisters():
            print(register,":",intepreter.readClassicRegister(register))
        



if __name__ == "__main__":
    main(sys.argv)