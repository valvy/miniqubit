package nl.hvanderheijden.miniqbt;
import java.io.File;
import java.nio.file.Files;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.StandardCopyOption;

public final class Globals{

    static {
        // Load the library. So it can be packaged together with the jar.
        // This will only load the javanativeMiniQbt it still requires the real shared object.
        
        final String tmpDirectory = System.getProperty("java.io.tmpdir");
        final String LIB_NAME = getLibraryName();
        File generatedDir = new File(tmpDirectory, "miniqbt" + System.nanoTime());
        if(!generatedDir.mkdir()){
            System.out.println("error");
        }
        generatedDir.deleteOnExit();
        File temp = new File(generatedDir, LIB_NAME);
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
        // todo make sure it works on OSX and Windows
        // Should test it though
        final String BIT_VERSION;
        if(System.getProperty("os.arch").contains("64")){
            BIT_VERSION = "x86_64";
        } else {
            BIT_VERSION = "x86";
        }
       
        final String OS_VERSION = System.getProperty("os.name");
        final String LIB_EXTENSION;
        if(OS_VERSION.contains("Linux")) {
            LIB_EXTENSION = "so";
        } else if (OS_VERSION.contains("Mac")) {
            LIB_EXTENSION = "dylib";
        } else {
            // Assume Windows
            LIB_EXTENSION = "dll";
        }

        return String.format(
            "/libJavaMiniQbtWrapper_%s_%s.%s", 
            BIT_VERSION, 
            OS_VERSION,
            LIB_EXTENSION
        );
    }

    private Globals(){
        throw new UnsupportedOperationException();
    }
    
    public static native String getName();

    public static native String getVersion();
}
