package com.matthijs.kropholler.jniarticle;

public class MyNativeObject {
    public native void printToStdOut();
    public native int addNumbers(int number1, int number2);
    public native void manipulateData(MyDataObject dataObject);
}
