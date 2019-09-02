#!/usr/bin/env python3
from PyMiniQbt import getVersion, getName, QasmAsyncInterpreter

import sys

def main(arguments):
    if(len(arguments) < 2):
        print("which file?")
        sys.exit(-1)

    amount = 100
    if(len(arguments) == 3):
        try:
            amount = int(arguments[2])
        except ValueError as ex:
            print("could not parse amount, using default", amount)
    print("Using", getName(), "version:", getVersion())
    with open(arguments[1]) as dat:
        src = dat.read()
        interpreter = QasmAsyncInterpreter()
        interpreter.interpret(src)
        hadError = interpreter.hasErrors()
        while interpreter.hasErrors():
            print(interpreter.getError())
        
        res = []
        for i in range(0,amount):
            for register in interpreter.getRegisters():
                for qReg in interpreter.getQuantumRegisters():
                    interpreter.resetSuperPosition(qReg)

                newResult = interpreter.readClassicResult(register)
                inList = False
                for j in range(0, len(res)):
                    dat, am = res[j]
                    if dat == newResult:
                        res[j] = dat , am + 1
                        inList = True
                        break

                if not inList:
                    dat = newResult.dataToString(), 1
                    res.append(dat)
        
        if hadError:
            print("Program completed with errors")
        else:
            print("Program completed without errors")
        print("Result","\t|\t", "amount of times found")
        for result, amount in res:
            print( result , "\t|\t" , amount)



if __name__ == "__main__":
    main(sys.argv)