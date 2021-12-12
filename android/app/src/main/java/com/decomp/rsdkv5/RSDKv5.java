package com.decomp.rsdkv5;

import android.Manifest;
import android.content.Context;
import android.os.Environment;

import java.io.File;

import org.libsdl.app.*;


public class RSDKv5 extends SDLActivity {
    @Override
    protected void onStart() {
        super.onStart();
        getBasePath();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            SDLActivity.mCurrentNativeState = SDLActivity.NativeState.PAUSED;
            SDLActivity.mNextNativeState = SDLActivity.NativeState.RESUMED;
        } 
        else {
            SDLActivity.mCurrentNativeState = SDLActivity.NativeState.RESUMED;
            SDLActivity.mNextNativeState = SDLActivity.NativeState.PAUSED;
        }

        SDLActivity.handleNativeState();
    }

    public String getBasePath() {
        Context c = getApplicationContext();
        requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0);
        String p = Environment.getExternalStorageDirectory().getAbsolutePath() + "/RSDK/v5";
        //getExternalStorageDirectory is deprecated. I do not care.
        new File(p).mkdirs();
        return p + "/";
    }

    public int getFocusState() {
        switch (mCurrentNativeState)
            case NativeState.INIT: return 0;
            case NativeState.RESUMED: return 1;
            case NativeState.PAUSED: return 2;
        }
        return -1;
    }
}
