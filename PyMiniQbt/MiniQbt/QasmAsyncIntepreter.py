import MiniQbtNative

class QasmAsyncIntepreter:
    def __init__(self):
        pass

    def doSomething(self):
        return MiniQbtNative.testMethod(10)

    def intepret(self, source):
        pass

    def getRegisters(self):
        pass

    def doesRegisterExists(self, name):
        return False

    def hasErrors(self):
        return True

    def getError(self):
        return "Not yet implemented"