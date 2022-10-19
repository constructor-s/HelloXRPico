//
// Created by Bill on 2022-10-18.
//

#include "MyControllerHandler.h"

MyControllerHandler::MyControllerHandler(JNIEnv * env, ANativeActivity * activity) : env(env), activity(activity) {

}

void MyControllerHandler::onActionStateBoolean(int side, XrAction action, const XrActionStateBoolean *actionState) {
    auto obj = activity->clazz;
    auto jmethodId = env->GetMethodID(env->GetObjectClass(obj), "onActionStateBooleanFromNative", "(JJJJJJ)V");

    jlong side_ = side;
    jlong action_ = reinterpret_cast<long>(action);
    jlong currentState = actionState->currentState;
    jlong changedSinceLastSync = actionState->changedSinceLastSync;
    jlong lastChangeTime = actionState->lastChangeTime;
    jlong isActive = actionState->isActive;
    env->CallVoidMethod(obj, jmethodId, side_, action_, currentState, changedSinceLastSync, lastChangeTime, isActive);
}

void MyControllerHandler::onActionStateFloat(int side, XrAction action, const XrActionStateFloat *actionState) {
    auto obj = activity->clazz;
    auto jmethodId = env->GetMethodID(env->GetObjectClass(obj), "onActionStateFloatFromNative", "(JJFJJJ)V");

    jlong side_ = side;
    jlong action_ = reinterpret_cast<long>(action);
    jfloat currentState = actionState->currentState;
    jlong changedSinceLastSync = actionState->changedSinceLastSync;
    jlong lastChangeTime = actionState->lastChangeTime;
    jlong isActive = actionState->isActive;
    env->CallVoidMethod(obj, jmethodId, side_, action_, currentState, changedSinceLastSync, lastChangeTime, isActive);
}
