package nl.hvanderheijden.miniqbt;
import java.util.List;
public class QasmAsyncInterpreter{

    public native void resetSuperPosition(String quantumRegister);

    public native void interpret(String src);

    public native List<String> getQuantumRegisters();

    public native List<String> getRegisters();

    public native List<Integer> readClassicRegister();

    public native boolean doesRegisterExists(String name);

    public native boolean hasErrors();

    public native String getErrors();

}
