package nl.hvanderheijden.miniqbt;
import java.io.Closeable;

public class QasmAsyncInterpreter implements Closeable {

    private long nativeQasmPointer;

    public QasmAsyncInterpreter() {
        this.nativeQasmPointer = 0;
        this.init();
    }

    private native void init();

    public native void resetSuperPosition(String quantumRegister);

    public native void interpret(String src);

    public native String[] getQuantumRegisters();

    public native String[] getRegisters();

    public native boolean[] readClassicRegister(String name);

    public native boolean doesRegisterExists(String name);

    public native boolean hasErrors();

    public native String getError();

    @Override
    public String toString() {
        return String.format("QasmAsyncInterpreter Ptr[%d]", this.nativeQasmPointer);
    }

    @Override
    public void close() {
        dispose();
    }

    private native void dispose();

}
