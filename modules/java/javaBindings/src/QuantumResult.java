package nl.hvanderheijden.miniqbt;

public class QuantumResult {

    private final String registerName;
    private final boolean[] registerData;

    public QuantumResult(final String registerName, boolean[] data ) {
        this.registerName = registerName;
        registerData = new boolean[data.length];
        for(int i = 0; i < data.length; i++) {
            registerData[i] = data[i];
        }
    }

    public String getName() {
        return this.registerName;
    }
    
    @Override
    public String toString() {
        return String.format("%s[%s]", this.registerName, this.dataToString());
    }

    public String dataToString() {
        String result = "";
        for(boolean in : this.registerData) {
            result += (in)? "0" : "1";
        }

        return result;
    }

    public int registerSize() {
        return this.registerData.length;
    }

    public boolean getData(int index) {
        return registerData[index];
    }
}