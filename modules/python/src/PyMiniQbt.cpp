#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <miniqbt/MiniQbt.hpp>


using namespace boost::python;

std::string getName() {
    return std::string(MiniQbt::NAME);
}

std::string getVersion() {
    return std::string(MiniQbt::VERSION);
}


BOOST_PYTHON_MODULE(PyMiniQbt) {

    def("getName", &getName);
    def("getVersion", &getVersion);

    class_<std::vector<std::string> >("StringVec")
        .def(vector_indexing_suite<std::vector<std::string>>());
    class_<MiniQbt::QuantumResult>("QuantumResult")
    .def("getName", &MiniQbt::QuantumResult::getName)
    .def("dataToString", &MiniQbt::QuantumResult::dataToString)
    .def("registerSize", &MiniQbt::QuantumResult::registerSize)
    .def("getData", &MiniQbt::QuantumResult::getData);

    class_<MiniQbt::QasmAsyncInterpreter>("QasmAsyncInterpreter").
    def("interpret", &MiniQbt::QasmAsyncInterpreter::interpret ).
    def("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    def("getQuantumRegisters", &MiniQbt::QasmAsyncInterpreter::getQuantumRegisters).
    def("resetSuperPosition", &MiniQbt::QasmAsyncInterpreter::resetSuperPosition).
    def("readClassicResult", &MiniQbt::QasmAsyncInterpreter::readClassicResult).
    def("doesRegisterExists", &MiniQbt::QasmAsyncInterpreter::doesRegisterExists).
    def("getRegisters",  &MiniQbt::QasmAsyncInterpreter::getRegisters).
    def("getError",  &MiniQbt::QasmAsyncInterpreter::getError).
    def("hasErrors", &MiniQbt::QasmAsyncInterpreter::hasErrors );

};