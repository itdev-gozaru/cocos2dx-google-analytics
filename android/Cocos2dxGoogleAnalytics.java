package org.cocos2dx.lib;

import com.google.android.gms.analytics.ExceptionReporter;
import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.HitBuilders;
import com.google.android.gms.analytics.Tracker;

import android.app.Activity;
import android.util.Log;

public class Cocos2dxGoogleAnalytics {
        private static final String TAG = Cocos2dxGoogleAnalytics.class.getName();

        private static Activity sActivity = null;

        private static boolean mTrackUncaughtExceptions = false;
        private static int mDispatchInterval = 20;
        private static int mLogLevel = 0;
        private static Tracker mTracker = null;

        private static void LOG(final String msg) {
                Log.d(TAG, msg);
        }

        private static boolean sInited = false;

        public static void init(final Activity activity) {
                LOG("init() called.");

                if (!sInited) {
                        sActivity = activity;

                        sInited = true;
                }
        }

        public static Activity getActivity() {
                return sActivity;
        }

        public static void setTrackUncaughtExceptions(final boolean trackUncaughtExceptions) {
                LOG("setTrackUncaughtExceptions(" + ((trackUncaughtExceptions) ? "True" : "False") + ") called.");

                mTrackUncaughtExceptions = trackUncaughtExceptions;
        }

        public static void setDispatchInterval(final int dispatchInterval) {
          LOG("setDispatchInterval(" + dispatchInterval + ") called.");

            mDispatchInterval = dispatchInterval;
        }

        public static void setLogLevel(final int logLevel) {
          LOG("setLogLevel(" + logLevel + ") called.");

            mLogLevel = logLevel;
        }

        public static void setTrackerWithTrackingId(final String trackingId) {
          LOG("setTrackerWithTrackingId(" + trackingId + ") called.");

          if (getActivity() != null) {
            getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                  mTracker = GoogleAnalytics.getInstance(getActivity()).newTracker(trackingId);
                  
                  // uncaught exceptin
                  if (Cocos2dxGoogleAnalytics.mTrackUncaughtExceptions) {
                        ExceptionReporter reporter = new ExceptionReporter(mTracker,
                        		Thread.getDefaultUncaughtExceptionHandler(),
                        		getActivity());
                        Thread.setDefaultUncaughtExceptionHandler(reporter);
                  }

                  // dispatch period
                  GoogleAnalytics.getInstance(getActivity()).setLocalDispatchPeriod(Cocos2dxGoogleAnalytics.mDispatchInterval);

                  // log level
                  GoogleAnalytics.getInstance(getActivity()).getLogger().setLogLevel(Cocos2dxGoogleAnalytics.mLogLevel);
            }
          });
          }
        }

        public static void sendScreen(final String screen) {
          LOG("sendScreen(" + screen + ") called.");

          if (getActivity() != null) {
            getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
            	if (mTracker != null) {
                  mTracker.setScreenName(screen);
                  mTracker.send(new HitBuilders.AppViewBuilder().build());
            	}
            }
          });
          }
        }

        public static void sendEvent(final String category, final String action, final String label, final int value) {
          LOG("sendEvent(" + category + ", " + action + ", " + label + ", " + value + ") called.");

          if (getActivity() != null) {
            getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                  if (mTracker != null) {
                	  mTracker.send(new HitBuilders.EventBuilder()
                      .setCategory(category)
                      .setAction(action)
                      .setLabel(label)
                      .setValue(value)
                      .build());
                  }
            }
          });
          }
        }

        public static void setCustomDimension(final int index, final String value) {
          LOG("setCustomDimension(" + index + ", " + value + ") called.");

          if (getActivity() != null) {
            getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
            	if (mTracker != null) {
                  mTracker.send(new HitBuilders.AppViewBuilder().setCustomDimension(index, value).build());
            	}
            }
          });
          }
        }
}
