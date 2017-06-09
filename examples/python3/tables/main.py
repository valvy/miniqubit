#!/usr/bin/env python3
from MiniQbt.Globals import getVersion, getName
from MiniQbt.Intepreter import QasmAsyncIntepreter
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
        intepreter = QasmAsyncIntepreter()
        intepreter.intepret(src)
        hadError = intepreter.hasErrors()
        while intepreter.hasErrors():
            print(intepreter.getError())
        
        res = []
        for i in range(0,amount):
            for register in intepreter.getRegisters():
                for qReg in intepreter.getQuantumRegisters():
                    intepreter.resetSuperPosition(qReg)

                newResult = intepreter.readClassicRegister(register)
                inList = False
                for j in range(0, len(res)):
                    dat, am = res[j]
                    if dat == newResult:
                        res[j] = dat , am + 1
                        inList = True
                        break

                if not inList:
                    dat = newResult, 1
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