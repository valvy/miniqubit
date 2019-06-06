package nl.hvanderheijden.miniqbt;


/**
 * @author H.J.M van der Heijden
 * Class that manages a quantum emulator for IBMQ.
 * This wraps primarily a C++ class.
 */
public class QasmAsyncInterpreter {

    /**
     * Pointer that stores the memory adress of the QasmAsyncInterpreter
     * Do not alter this!
     */
    private long nativeQasmPointer;

    public QasmAsyncInterpreter() {
        this.nativeQasmPointer = 0;
        this.init();
    }

    /**
     * Initializes the native code.
     * Which sets makes up memory and sets the pointer.
     */
    private native void init();

    public native void resetSuperPosition(String quantumRegister);

    public native void interpret(String src);

    public native String[] getQuantumRegisters();

    public native String[] getRegisters();

    /**
     * Returns
     * @param name
     * @return
     */
    public native boolean[] readClassicRegister(String name);

    public native boolean doesRegisterExists(String name);

    public native boolean hasErrors();

    public native String getError();

    @Override
    public boolean equals(Object other) {
        if(other instanceof QasmAsyncInterpreter) {
            return (((QasmAsyncInterpreter)other).nativeQasmPointer == this.nativeQasmPointer);
        }
        return false;
    }

    @Override
    public String toString() {
        return String.format("%d", this.nativeQasmPointer);
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            dispose();
            System.out.println("Tesdsafafdst");
        } finally {
            super.finalize();
        }
       
    }

    private native void dispose();

}
