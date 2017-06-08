import MiniQbtNative


class QasmAsyncIntepreter:
    '''
    Class for asynchronous intepretation of quantum assembly code.
    This wraps the QasmAsyncClass from c++ MiniQbt.
    '''
    def __init__(self):
        self.__pointer = MiniQbtNative.init_qasm_async_intepreter(self)

    def intepret(self, source):
        '''
        Inteprets a block of quantum assembly code.
        @param source, the source code in string form.
        '''
        return MiniQbtNative.async_intepret(self.__pointer,source)

    def getRegisters(self):
        '''
        Get all the active classical registers in the quantum computer.
        '''
        return MiniQbtNative.qasm_async_intepreter_get_registers(self.__pointer)

    def readClassicRegister(self, name):
        '''
        Reads the specified classic processor in the quantum computer.
        @param name, the classic processor name
        @return the register value as string.
        '''
        return MiniQbtNative.qasm_async_read_classic_register(self.__pointer, name)

    def doesRegisterExists(self, name):
        '''
        Checks if a classical register exists.
        @param name, the classic register name.
        @return true if register exists, false if the register does not exists.
        '''
        for i in self.getRegisters():
            if i is name:
                return True
        return False

    def hasErrors(self):
        '''
        Check if the quantum computer has an error.
        Returns either a true or false.
        '''
        return MiniQbtNative.qasm_async_intepreter_has_errors(self.__pointer)

    def getError(self):
        '''
        Get's the error from the quantum computer.
        This will remove the error from the list of errors.
        Returns a string with the error message
        '''
        return MiniQbtNative.qasm_async_intepreter_get_error(self.__pointer) 

    def __del__(self):
        MiniQbtNative.destroy_qasm_async_intepreter(self.__pointer)