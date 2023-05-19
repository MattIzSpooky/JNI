#include "com_matthijs_kropholler_jniarticle_MyNativeObject.h"
#include <iostream> // this is required for std::cout
#include <string> // This is required for std::string
#include <algorithm> // this is required for std::reverse


JNIEXPORT void JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_printToStdOut (JNIEnv* javaEnv, jobject thisJavaObject) {
     std::cout << "Hello from C++ !!" << std::endl; // This will write "Hello from C++ !!" to std out (likely a terminal)
}

JNIEXPORT jint JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_addNumbers (JNIEnv * javaEnv, jobject thisJavaObject, jint number1, jint number2) {
    return number1 + number2; // Add the numbers together
}

JNIEXPORT void JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_manipulateData(JNIEnv* javaEnv, jobject thisJavaObject, jobject myJavaDataObject) {
    // Get the Java class of the object because we are going to need to get the method ids
    jclass myDataObjectClass = javaEnv->GetObjectClass(myJavaDataObject);

    // In order to call a Java method. we need the method ids of the methods we are trying to call
    jmethodID getNameMethodId =javaEnv->GetMethodID(myDataObjectClass, "getName", "()Ljava/lang/String;"); // the 2nd argument is the return type
    jmethodID setNameMethodId =javaEnv->GetMethodID(myDataObjectClass, "setName", "(Ljava/lang/String;)V"); // the 2nd argument is the argument of type String and return type void

    // This is basically the same as calling "getName" on an instance of the DataObject class.
    jstring rawJavaString = (jstring)javaEnv->CallObjectMethod(myJavaDataObject, getNameMethodId);

    // Convert the C++ representation of a Java string to a regular C++ string so that we can perform operations on it.

    // Get the raw string
    jboolean isCopy;
    const char* utfChars = javaEnv->GetStringUTFChars(rawJavaString, &isCopy);
    // Put the raw string in a C++ string object. std::string will take care of the string's life cycle. We do not need to delete the data once we are done with it.
    // When the string leaves its defined scope, it will automatically be cleaned up.
    std::string nativeString(utfChars);
    // Since we have copied the contents of the original string we need to release it so that we don't leak memory
    javaEnv->ReleaseStringUTFChars(rawJavaString, utfChars);

    // Now that we got our hands onto a native string, we can do some operations on it. For simplicity sake we will just reverse the string.
    std::reverse(nativeString.begin(), nativeString.end());

    // After our native operation, let's put the data back onto our Java object.
    // Here we call a void method on our instance of DataObject and we call "setName". As argument we give it a new Java string
    javaEnv->CallVoidMethod(myJavaDataObject, setNameMethodId, javaEnv->NewStringUTF(nativeString.c_str()));
}