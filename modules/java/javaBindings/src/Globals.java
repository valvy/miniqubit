package nl.hvanderheijden.miniqbt;
import java.io.File;
import java.nio.file.Files;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.StandardCopyOption;

public final class Globals{

    static {
      //  System.load("/home/heiko/Documents/Projectjes/miniqubit/build/modules/java/javaBindings/libMiniQbt.so");
        System.load("/home/heiko/Documents/Projectjes/miniqubit/build/modules/java/javaBindings/libJavaMiniQbtWrapper.so");
    }
    
    /*
    static {
        final String tmpDirectory = System.getProperty("java.io.tmpdir");
        final String LIB_NAME = getLibraryName();
        File generatedDir = new File(tmpDirectory, "miniqbt" + System.nanoTime());
        if(!generatedDir.mkdir()){
            System.out.println("error");
        }
        generatedDir.deleteOnExit();
        File temp = new File(generatedDir, LIB_NAME);//"/libJavaMiniQbtWrapper.so");
        try (final InputStream is = Globals.class.getResourceAsStream(LIB_NAME)) {
            Files.copy(is, temp.toPath(), StandardCopyOption.REPLACE_EXISTING);   
        } catch (final IOException exception ){
            System.out.println(exception.getMessage());
        }
        try {
            System.load(temp.getAbsolutePath()); 
        } finally {
            temp.delete();
        }
        
    }

  
    private static String getLibraryName(){
        final String BIT_VERSION;
        if(System.getProperty("os.arch").contains("64")){
            BIT_VERSION = "x86_64";
        } else {
            BIT_VERSION = "x86";
        }
       
        final String OS_VERSION = System.getProperty("os.name");
        return String.format(
            "/libJavaMiniQbtWrapper_%s_%s.so", 
            BIT_VERSION, 
            OS_VERSION);
    }
*/
    private Globals(){
        throw new UnsupportedOperationException();
    }
    
    public static native String getName();

    public static native String getVersion();

    public static void main(String[] args){
        System.out.println(getName() + " : " + getVersion());
        System.out.println("teste");
       try (final QasmAsyncInterpreter inte = new QasmAsyncInterpreter()) {
       //     inte.init();
            inte.interpret("qreg a[5];" +
                            "creg b[5];"+
                            "h a;" +
                            "measure a -> b;"
                            
            );
            if(!inte.hasErrors()) {
                for(boolean i : inte.readClassicRegister("b")) {
                    System.out.println(i);
                }
            } else {
                while(inte.hasErrors()) {
                    System.out.println(inte.getError());
                }
            }

        } finally {

        }
        //QasmAsyncInterpreter inte = new QasmAsyncInterpreter();
        //inte.init();
        //inte.close();

      
    }
}
