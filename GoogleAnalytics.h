#pragma once

#include <memory>

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

class GoogleAnalyticsImpl;

class GoogleAnalytics : public cocos2d::Node {
public:
    enum LogLevel {
        NONE = 0,
        ERROR,
        WARNING,
        INFO,
        VERBOSE,
    };

    GoogleAnalytics();

    CREATE_FUNC(GoogleAnalytics);

    /**
     * @brief 捕捉しない例外をトラックするか設定する
     * @param trackUncaughtExceptions トラックする場合、true
     */
    void setTrackUncaughtExceptions(bool trackUncaughtExceptions);

    /**
     * @brief 処理間隔を設定する
     * @param dispatchInterval 処理間隔(s)
     */
    void setDispatchInterval(int dispatchInterval);

    /**
     * @brief ログレベルを設定する
     * @param logLevel ログレベル
     */
    void setLogLevel(LogLevel logLevel);

    /**
     * @brief トラッキングIDを設定する
     * @param トラッキングID
     */
    void setTrackerWithTrackingId(const std::string& trackingId);

    /**
     * @brief カスタムディメンションを設定する
     * @param インデックス
     * @param 値
     */
    void setCustomDimension(int index, const std::string& value);

    /**
     * @brief スクリーンを送信する
     * @param screen スクリーン
     */
    void sendScreen(const std::string& screen);

    /**
     * @brief イベントを送信する
     * @param category カテゴリ
     * @param action アクション
     * @param label ラベル
     * @param value 値
     */
    void sendEvent(const std::string& category,
                   const std::string& action,
                   const std::string& label,
                   long value);
private:
    std::shared_ptr<GoogleAnalyticsImpl> impl_;
};

NS_CC_EXT_END
