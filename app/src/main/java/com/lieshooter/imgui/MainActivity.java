package com.lieshooter.imgui;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;
import com.lieshooter.imgui.R;

public class MainActivity extends Activity {
    private static final String TAG = "NativeLibLoader";

    static {
        try {
            System.loadLibrary("AkSoundEngine+");
            Log.i(TAG, "Native library loaded successfully");
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "Failed to load native library: " + e.getMessage());
        }
    }

    public native String getNativeMessage();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // FIX: Add explicit cast to TextView
        TextView tv = (TextView) findViewById(R.id.sample_text);
        
        try {
            String message = getNativeMessage();
            tv.setText(message);
        } catch (Exception e) {
            tv.setText("Native method call failed");
            Log.e(TAG, "Native method error: " + e.getMessage());
        }
    }
}
