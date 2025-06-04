package com.lieshooter.imgui;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity {
    private static final String TAG = "NativeLibLoader";

    // Load native library
    static {
        try {
            // Use the actual library name from your Android.mk (LOCAL_MODULE)
            System.loadLibrary("AkSoundEngine+");
            Log.i(TAG, "Native library loaded successfully");
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "Failed to load native library: " + e.getMessage());
        }
    }

    // Native method declaration
    public native String getNativeMessage();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        TextView tv = findViewById(R.id.sample_text);
        
        try {
            // Call native method
            String message = getNativeMessage();
            tv.setText(message);
        } catch (Exception e) {
            tv.setText("Native method call failed");
            Log.e(TAG, "Native method error: " + e.getMessage());
        }
    }
}
