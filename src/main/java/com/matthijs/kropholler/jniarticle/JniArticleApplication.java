package com.matthijs.kropholler.jniarticle;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.nio.file.Paths;

@SpringBootApplication
public class JniArticleApplication implements CommandLineRunner {
    Logger logger = LoggerFactory.getLogger(JniArticleApplication.class);

    static {
        final String userDirectory = System.getProperty("user.dir"); // This will get the current working folder.
        final String sharedLibsDirName = "sharedlibs"; // The directory where our shared library is stored
        final String sharedLibraryName = System.mapLibraryName("my_native_library"); // This will map the library name to the platform specific name. on MacOS this will become libmy_native_library.dylib

        // The program will not start if it cannot find the library
        System.load(Paths.get(userDirectory, sharedLibsDirName,sharedLibraryName).toString());
    }

    public static void main(String... args) {
        SpringApplication.run(JniArticleApplication.class, args);
    }

    @Override
    public void run(String... args) throws Exception {
        var nativeObject = new MyNativeObject();

        nativeObject.printToStdOut();

        int result = nativeObject.addNumbers(1, 1);
        logger.info("Result from native code: {}", result);

        MyDataObject dataObject = new MyDataObject();
        dataObject.setName("Matthijs Kropholler");

        logger.info("getName before running native code: {}", dataObject.getName());
        nativeObject.manipulateData(dataObject);
        logger.info("getName after running native code: {}", dataObject.getName());
    }
}
