#pragma once

#include "cocos2d.h"

#include <jni.h>
#include <string>

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackUncaughtExceptionsJni(bool trackUncaughtExceptions);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setDispatchIntervalJni(int dispatchInterval);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setLogLevelJni(int logLevel);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackerWithTrackingIdJni(const std::string& trackingId);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendScreenJni(const std::string& screen);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendEventJni(const std::string& category,
                                                                    const std::string& action,
                                                                    const std::string& label,
                                                                    long value);
    void Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setCustomDimensionJni(int index, const std::string& value);
}
