#pragma once

#include "extensions/ExtensionMacros.h"

#include "GoogleAnalytics.h"

NS_CC_EXT_BEGIN

class GoogleAnalyticsImpl {
public:
    virtual ~GoogleAnalyticsImpl() {}

    virtual void setTrackUncaughtExceptions(bool trackUncaughtExceptions) =  0;
    virtual void setDispatchInterval(int dispatchInterval) = 0;
    virtual void setLogLevel(GoogleAnalytics::LogLevel logLevel) = 0;
    virtual void setTrackerWithTrackingId(const std::string& trackingId) = 0;
    virtual void setCustomDimension(int index, const std::string& value) = 0;
    virtual void sendScreen(const std::string& screen) = 0;
    virtual void sendEvent(const std::string& category,
                           const std::string& action,
                           const std::string& label,
                           long value) = 0;

};

NS_CC_EXT_END
