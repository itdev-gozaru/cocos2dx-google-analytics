#include "GoogleAnalytics.h"

#include "GoogleAnalyticsImpl.h"

USING_NS_CC_EXT;

void GoogleAnalytics::setTrackUncaughtExceptions(bool trackUncaughtExceptions) {
    impl_->setTrackUncaughtExceptions(trackUncaughtExceptions);
}

void GoogleAnalytics::setDispatchInterval(int dispatchInterval) {
    impl_->setDispatchInterval(dispatchInterval);
}

void GoogleAnalytics::setLogLevel(LogLevel logLevel) {
    impl_->setLogLevel(logLevel);
}

void GoogleAnalytics::setTrackerWithTrackingId(const std::string& trackingId) {
    impl_->setTrackerWithTrackingId(trackingId);
}

void GoogleAnalytics::setCustomDimension(int index, const std::string &value) {
  impl_->setCustomDimension(index, value);
}

void GoogleAnalytics::sendScreen(const std::string& screen) {
    impl_->sendScreen(screen);
}

void GoogleAnalytics::sendEvent(const std::string &category,
                                const std::string &action,
                                const std::string &label,
                                long value) {
    impl_->sendEvent(category, action, label, value);
}
