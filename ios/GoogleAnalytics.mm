#include "GoogleAnalytics.h"

#include "GoogleAnalyticsImpl.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "sdk/GoogleAnalytics/Library/GAI.h"
#import "sdk/GoogleAnalytics/Library/GAIDictionaryBuilder.h"
#import "sdk/GoogleAnalytics/Library/GAIFields.h"

USING_NS_CC_EXT;

#pragma mark - Definition of Impl
class GoogleAnalyticsImplIOS : public GoogleAnalyticsImpl {
    void setTrackUncaughtExceptions(bool trackUncaughtExceptions) {
        CCLOG("GoogleAnalyticsImplIOS::setTrackUncaughtExceptions(%s) called.",
              (trackUncaughtExceptions) ? "TRUE" : "FALSE");

        [GAI sharedInstance].trackUncaughtExceptions = trackUncaughtExceptions;
    }
    
    void setDispatchInterval(int dispatchInterval) {
        CCLOG("GoogleAnalyticsImplIOS::setDispatchInterval(%d) called.",
              dispatchInterval);

        [GAI sharedInstance].dispatchInterval = dispatchInterval;
    }
    
    void setLogLevel(GoogleAnalytics::LogLevel logLevel) {
        CCLOG("GoogleAnalyticsImplIOS::setLogLevel(%u) called.",
              logLevel);
        
        // iOSの定数に変換
        auto gaLevel = kGAILogLevelNone;
        switch (logLevel) {
            case cocos2d::extension::GoogleAnalytics::NONE:
                gaLevel = kGAILogLevelNone;
                break;
            case cocos2d::extension::GoogleAnalytics::ERROR:
                gaLevel = kGAILogLevelError;
                break;
            case cocos2d::extension::GoogleAnalytics::WARNING:
                gaLevel = kGAILogLevelWarning;
                break;
            case cocos2d::extension::GoogleAnalytics::INFO:
                gaLevel = kGAILogLevelInfo;
                break;
            case cocos2d::extension::GoogleAnalytics::VERBOSE:
                gaLevel = kGAILogLevelVerbose;
                break;
            default:
                break;
        }

        [[[GAI sharedInstance] logger] setLogLevel:gaLevel];
    }
    
    void setTrackerWithTrackingId(const std::string& trackingId) {
        CCLOG("GoogleAnalyticsImplIOS::setTrackerWithTrackingId(%s) called.",
              trackingId.c_str());

        NSString* nsTrackingId = [NSString stringWithUTF8String:trackingId.c_str()];
        auto tracker = [[GAI sharedInstance] trackerWithTrackingId:nsTrackingId];
        [[GAI sharedInstance] setDefaultTracker:tracker];
    }
  
    void setCustomDimension(int index, const std::string& value) {
        CCLOG("GoogleAnalyticsImplIOS::setCustomDimension(%d,%s) called.",
              index, value.c_str());
    
        NSString* nsValue = [NSString stringWithUTF8String:value.c_str()];
        auto tracker = [[GAI sharedInstance] defaultTracker];
        [tracker set:[GAIFields customDimensionForIndex:index] value:nsValue];
    }

    void sendScreen(const std::string& screen) {
        CCLOG("GoogleAnalyticsImplIOS::sendScreen(%s) called.",
              screen.c_str());

        NSString* nsScreen = [NSString stringWithUTF8String:screen.c_str()];
        
        auto tracker = [[GAI sharedInstance] defaultTracker];
        [tracker set:kGAIScreenName value:nsScreen];
        [tracker send:[[GAIDictionaryBuilder createAppView] build]];
    }
    
    void sendEvent(const std::string& category,
                   const std::string& action,
                   const std::string& label,
                   long value) {
        CCLOG("GoogleAnalyticsImplIOS::sendScreen(%s, %s, %s, %ld) called.",
              category.c_str(), action.c_str(), label.c_str(), value);

        NSString* nsCategory = [NSString stringWithUTF8String:category.c_str()];
        NSString* nsAction = [NSString stringWithUTF8String:action.c_str()];
        NSString* nsLabel = [NSString stringWithUTF8String:label.c_str()];
        NSNumber* nsValue = [NSNumber numberWithLong:value];
        
        auto tracker = [[GAI sharedInstance] defaultTracker];
        [tracker send:[[GAIDictionaryBuilder createEventWithCategory:nsCategory
                                                              action:nsAction
                                                               label:nsLabel
                                                               value:nsValue] build]];
    }

};

#pragma mark - Implement of GoogleAnalytics
GoogleAnalytics::GoogleAnalytics() {
    impl_ = std::make_shared<GoogleAnalyticsImplIOS>();
}
