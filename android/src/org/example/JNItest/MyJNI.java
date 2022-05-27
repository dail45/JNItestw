package org.example.JNItest;
import android.app.Activity;

public class MyJNI
{
    private final Activity m_MainActivity;
    public MyJNI(final Activity MainActivity) {
        m_MainActivity = MainActivity;
    }
    public native String nativeFun();
    public String jniFun() {
        String a = nativeFun();
        System.out.println(a);
        return "Java: " + a;
    }
}
