#include "Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics.h"

#include <jni.h>

#include "jni/JniHelper.h"
#include "../GoogleAnalytics.h"

#define LOG_TAG "GoogleAnalyticsJni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackUncaughtExceptionsJni(bool trackUncaughtExceptions) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxGoogleAnalytics", "setTrackUncaughtExceptions", "(Z)V")) {
    LOGD("Failed to find static method of setTrackUncaughtExceptions");
    return;
  }
  t.env->CallStaticVoidMethod(t.classID, t.methodID, trackUncaughtExceptions);
  t.env->DeleteLocalRef(t.classID);
}

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setDispatchIntervalJni(int dispatchInterval) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxGoogleAnalytics", "setDispatchInterval", "(I)V")) {
    LOGD("Failed to find static method of setDispatchInterval");
    return;
  }
  t.env->CallStaticVoidMethod(t.classID, t.methodID, dispatchInterval);
  t.env->DeleteLocalRef(t.classID);
}

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setLogLevelJni(int logLevel) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxGoogleAnalytics", "setLogLevel", "(I)V")) {
    LOGD("Failed to find static method of setLogLevel");
    return;
  }
  t.env->CallStaticVoidMethod(t.classID, t.methodID, logLevel);
  t.env->DeleteLocalRef(t.classID);
}

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackerWithTrackingIdJni(const std::string& trackingId) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxGoogleAnalytics", "setTrackerWithTrackingId", "(Ljava/lang/String;)V")) {
    LOGD("Failed to find static method of setTrackerWithTrackingId");
    return;
  }
  jstring jTrackingId = t.env->NewStringUTF(trackingId.c_str());
  t.env->CallStaticVoidMethod(t.classID, t.methodID, jTrackingId);
  t.env->DeleteLocalRef(jTrackingId);
  t.env->DeleteLocalRef(t.classID);
}

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendScreenJni(const std::string& screen) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxGoogleAnalytics", "sendScreen", "(Ljava/lang/String;)V")) {
    LOGD("Failed to find static method of sendScreen");
    return;
  }
  jstring jScreen = t.env->NewStringUTF(screen.c_str());
  t.env->CallStaticVoidMethod(t.classID, t.methodID, jScreen);
  t.env->DeleteLocalRef(jScreen);
  t.env->DeleteLocalRef(t.classID);
}

void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendEventJni(const std::string& category,
                                                                const std::string& action,
                                                                const std::string& label,
                                                                long value) {
  cocos2d::JniMethodInfo t;
  if (!cocos2d::JniHelper::getStaticMethodInfo(t,
                                               "org/cocos2dx/lib/Cocos2dxGoogleAnalytics",
                                               "sendEvent",
                                               "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")) {
    LOGD("Failed to find static method of sendEvent");
    return;
  }
  jstring jCategory = t.env->NewStringUTF(category.c_str());
  jstring jAction= t.env->NewStringUTF(action.c_str());
  jstring jLabel= t.env->NewStringUTF(label.c_str());
  t.env->CallStaticVoidMethod(t.classID, t.methodID, jCategory, jAction, jLabel, (int) value);
  t.env->DeleteLocalRef(jCategory);
  t.env->DeleteLocalRef(jAction);
  t.env->DeleteLocalRef(jLabel);
  t.env->DeleteLocalRef(t.classID);
}
}
