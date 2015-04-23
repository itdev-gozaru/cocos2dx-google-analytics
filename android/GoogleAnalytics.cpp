#include "../GoogleAnalytics.h"

#include <jni.h>

#include "../GoogleAnalyticsImpl.h"

#include "../jni/Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics.h"

USING_NS_CC_EXT;

class GoogleAnalyticsImplAndroid : public GoogleAnalyticsImpl {
public:
  void setTrackUncaughtExceptions(bool trackUncaughtExceptions) {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackUncaughtExceptionsJni(trackUncaughtExceptions);
  }

  void setDispatchInterval(int dispatchInterval) {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setDispatchIntervalJni(dispatchInterval);
  }

  void setLogLevel(GoogleAnalytics::LogLevel logLevel)  {
    /*
     * C++上のログレベル
    enum LogLevel {
        NONE = 0,
        ERROR,
        WARNING,
        INFO,
        VERBOSE,
    };
     */
    /**
     * JAVA上のログレベル
   public static enum LogLevel
   {
     VERBOSE, 0
     INFO,    1
     WARNING, 2
     ERROR;   3
   }
   */
    int level = 3;
    switch (logLevel) {
      case GoogleAnalytics::LogLevel::NONE:
        level = 3;
        break;
      case GoogleAnalytics::LogLevel::ERROR:
        level = 3;
        break;
      case GoogleAnalytics::LogLevel::WARNING:
        level = 2;
        break;
      case GoogleAnalytics::LogLevel::INFO:
        level = 1;
        break;
      case GoogleAnalytics::LogLevel::VERBOSE:
        level = 0;
        break;
      default:
        break;
    }
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setLogLevelJni(level);
  }

  void setTrackerWithTrackingId(const std::string& trackingId) {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setTrackerWithTrackingIdJni(trackingId);
  }

  void setCustomDimension(int index, const std::string& value) {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_setCustomDimensionJni(index, value);
  }

  void sendScreen(const std::string& screen)  {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendScreenJni(screen);
  }

  void sendEvent(const std::string& category,
                         const std::string& action,
                         const std::string& label,
                         long value)  {
    Java_org_cocos2dx_lib_Cocos2dxGoogleAnalytics_sendEventJni(category, action, label, value);
  }
};

GoogleAnalytics::GoogleAnalytics() {
    impl_ = std::make_shared<GoogleAnalyticsImplAndroid>();
}
