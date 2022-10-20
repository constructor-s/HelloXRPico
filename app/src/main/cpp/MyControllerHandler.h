//
// Created by Bill on 2022-10-18.
//

#ifndef HELLOXRPICO_MYCONTROLLERHANDLER_H
#define HELLOXRPICO_MYCONTROLLERHANDLER_H

#include <jni.h>
#include <android_native_app_glue.h>
#include <openxr/openxr.h>

class MyControllerHandler {
public:
    MyControllerHandler(JNIEnv * env, ANativeActivity * activity);
    void onActionStateBoolean(int side, XrAction action, const XrActionStateBoolean *actionState);
    void onActionStateFloat(int side, XrAction action, const XrActionStateFloat *actionState);
private:
    JNIEnv *env;
    ANativeActivity *activity;
    jmethodID onActionStateBooleanFromNativeMethodId;
    jmethodID onActionStateFloatFromNativeMethodId;
};


#endif //HELLOXRPICO_MYCONTROLLERHANDLER_H
