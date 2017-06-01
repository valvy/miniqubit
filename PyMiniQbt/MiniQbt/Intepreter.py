import MiniQbtNative


class QasmAsyncIntepreter:
    def __init__(self):
        self.__pointer = MiniQbtNative.init_qasm_async_intepreter(self)

    def intepret(self, source):
        return MiniQbtNative.async_intepret(self.__pointer,source)

    def getRegisters(self):
        return MiniQbtNative.qasm_async_intepreter_get_registers(self.__pointer)

    def readClassicRegister(self, name):
        return MiniQbtNative.qasm_async_read_classic_register(self.__pointer, name)

    def doesRegisterExists(self, name):
        for i in self.getRegisters():
            if i is name:
                return True
        return False

    def hasErrors(self):
        return MiniQbtNative.qasm_async_intepreter_has_errors(self.__pointer)

    def getError(self):
        return MiniQbtNative.qasm_async_intepreter_get_error(self.__pointer) 

    def __del__(self):
        MiniQbtNative.destroy_qasm_async_intepreter(self.__pointer)