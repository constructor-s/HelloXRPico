package com.shirunjie.helloxrpico

import android.app.NativeActivity
import android.media.AudioManager
import android.media.ToneGenerator
import android.os.Bundle
import android.os.Handler
import android.util.Log
import java.util.*

class MainActivity : NativeActivity(), Runnable {
    val actionQueue: Queue<Float> = LinkedList<Float>()
    var isNotPaused = true
    val handler = Handler()
    private lateinit var toneGenerator: ToneGenerator

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        toneGenerator = ToneGenerator(AudioManager.STREAM_MUSIC, 100)
    }

    override fun onResume() {
        super.onResume()
        isNotPaused = true
        handler.post(this)
    }

    override fun run() {
        if (this.isNotPaused) {
            while (actionQueue.isNotEmpty()) {
                if (actionQueue.remove() > 0.5) {
                    toneGenerator.startTone(ToneGenerator.TONE_DTMF_9, 100)
                    actionQueue.clear()
                }
            }
            handler.postDelayed(this, 10)
        }
    }

    override fun onPause() {
        super.onPause()
        isNotPaused = false
    }

    override fun onDestroy() {
        super.onDestroy()
        toneGenerator.release()
    }

    fun onActionStateBooleanFromNative(side: Long, action: Long, currentState: Long, changedSinceLastSync: Long, lastChangeTime: Long, isActive: Long) {
        actionQueue.add(currentState * 1.0f)
        Log.i("MainActivity", "onActionStateBooleanFromNative: currentThread = ${Thread.currentThread()}, " +
                "side = $side, " +
                "action = $action, " +
                "currentState = $currentState, " +
                "changedSinceLastSync = $changedSinceLastSync, " +
                "lastChangeTime = $lastChangeTime, " +
                "isActive = $isActive")
    }

    fun onActionStateFloatFromNative(side: Long, action: Long, currentState: Float, changedSinceLastSync: Long, lastChangeTime: Long, isActive: Long) {
        actionQueue.add(currentState)
        Log.i("MainActivity", "onActionStateFloatFromNative: currentThread = ${Thread.currentThread()}, " +
                "side = $side, " +
                "action = $action, " +
                "currentState = $currentState, " +
                "changedSinceLastSync = $changedSinceLastSync, " +
                "lastChangeTime = $lastChangeTime, " +
                "isActive = $isActive")
    }

    companion object {
        init {
            // Note: Must handle loading of dependent shared libraries manually before
            // the shared library that depends on them is loaded, since there is not
            // currently a way to specify a shared library dependency for NativeActivity
            // via the manifest meta-data.
            System.loadLibrary("openxr_loader")
            System.loadLibrary("hello_xr")
        }
    }
}