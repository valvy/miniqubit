#if defined(__EMSCRIPTEN__)
#include "miniqbt/MiniQbt.hpp"
#include <emscripten/bind.h>
/**
 * When the emscripten compiler is doing it's thing. 
 * Expose the QasmAsyncInterpreter
 */

std::string getName() {
    return MiniQbt::NAME;
}

std::string getVersion() {
    return MiniQbt::VERSION;
}


EMSCRIPTEN_BINDINGS(MiniQbt) {

    
    //register_vector<std::string>("VectorString");
    //register_vector<int>("QuantumResult");
    emscripten::class_<MiniQbt::QasmAsyncInterpreter>("QasmAsyncInterpreter").
    constructor().
    function("interpret", &MiniQbt::QasmAsyncInterpreter::interpret ).
    function("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    function("getQuantumRegisters", &MiniQbt::QasmAsyncInterpreter::getQuantumRegisters).
    function("resetSuperPosition", &MiniQbt::QasmAsyncInterpreter::resetSuperPosition).
    function("readClassicRegister", &MiniQbt::QasmAsyncInterpreter::readClassicRegister).
    function("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    function("getRegisters",  &MiniQbt::QasmAsyncInterpreter::getRegisters).
    function("getError",  &MiniQbt::QasmAsyncInterpreter::getError).
    function("hasErrors", &MiniQbt::QasmAsyncInterpreter::hasErrors );

    emscripten::function("getName", &getName);
    emscripten::function("getVersion", &getVersion);
}


#endif
