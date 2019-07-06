#if defined(__EMSCRIPTEN__)
#include "miniqbt/MiniQbt.hpp"
#include <emscripten/bind.h>


/**
 * When the emscripten compiler is doing it's thing. 
 * Expose the QasmAsyncInterpreter
 */

EMSCRIPTEN_BINDINGS(MiniQbt) {
    emscripten::class_<MiniQbt::QuantumResult>("QuantumResult").
    constructor().
    function("getName", &MiniQbt::QuantumResult::getName).
    function("dataToString", &MiniQbt::QuantumResult::dataToString).
    function("registerSize", &MiniQbt::QuantumResult::registerSize).
    function("getData", &MiniQbt::QuantumResult::getData);
    
    emscripten::register_vector<std::string>("RegisterNames");
    emscripten::class_<MiniQbt::QasmAsyncInterpreter>("QasmAsyncInterpreter").
    constructor().
    function("interpret", &MiniQbt::QasmAsyncInterpreter::interpret ).
    function("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    function("getQuantumRegisters", &MiniQbt::QasmAsyncInterpreter::getQuantumRegisters).
    function("resetSuperPosition", &MiniQbt::QasmAsyncInterpreter::resetSuperPosition).
    function("readClassicResult", &MiniQbt::QasmAsyncInterpreter::readClassicResult).
    function("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    function("getRegisters",  &MiniQbt::QasmAsyncInterpreter::getRegisters).
    function("getError",  &MiniQbt::QasmAsyncInterpreter::getError).
    function("hasErrors", &MiniQbt::QasmAsyncInterpreter::hasErrors );

    emscripten::constant("NAME", std::string(MiniQbt::NAME));
    emscripten::constant("VERSION", std::string(MiniQbt::VERSION));
}


#endif
