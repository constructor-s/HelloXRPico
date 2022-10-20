//
// Created by Bill on 2022-10-18.
//

#include "MyControllerHandler.h"

MyControllerHandler::MyControllerHandler(JNIEnv * env, ANativeActivity * activity)
    : env(env)
    , activity(activity)
    , onActionStateBooleanFromNativeMethodId(env->GetMethodID(env->GetObjectClass(activity->clazz), "onActionStateBooleanFromNative", "(JJJJJJ)V"))
    , onActionStateFloatFromNativeMethodId(env->GetMethodID(env->GetObjectClass(activity->clazz), "onActionStateFloatFromNative", "(JJFJJJ)V")) {
}

void MyControllerHandler::onActionStateBoolean(int side, XrAction action, const XrActionStateBoolean *actionState) {
    auto obj = activity->clazz;
    auto jmethodId = onActionStateBooleanFromNativeMethodId;

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
    auto jmethodId = onActionStateFloatFromNativeMethodId;

    jlong side_ = side;
    jlong action_ = reinterpret_cast<long>(action);
    jfloat currentState = actionState->currentState;
    jlong changedSinceLastSync = actionState->changedSinceLastSync;
    jlong lastChangeTime = actionState->lastChangeTime;
    jlong isActive = actionState->isActive;
    env->CallVoidMethod(obj, jmethodId, side_, action_, currentState, changedSinceLastSync, lastChangeTime, isActive);
}
