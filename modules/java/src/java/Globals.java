package nl.hvanderheijden.miniqbt;

public class Globals{
    static {
        System.load("/home/hheijden/Desktop/miniqubit/build/modules/java/libJavaMiniQbtWrapper.so");
    }
    
    public static native String getName();

    public static native String getVersion();

    public static void main(String[] args){
        //Globals s = new Globals();
        System.out.println(getName() + " : " + getVersion());
        System.out.println("teste");
    }
}
