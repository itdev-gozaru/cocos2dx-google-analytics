package org.cocos2dx.lib;

import java.util.HashMap;

import com.google.analytics.tracking.android.ExceptionReporter;
import com.google.analytics.tracking.android.Fields;
import com.google.analytics.tracking.android.GAServiceManager;
import com.google.analytics.tracking.android.GoogleAnalytics;
import com.google.analytics.tracking.android.Logger.LogLevel;
import com.google.analytics.tracking.android.MapBuilder;
import com.google.analytics.tracking.android.Tracker;
import com.google.tagmanager.protobuf.WireFormat.FieldType;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.util.Log;

public class Cocos2dxGoogleAnalytics {
        private static final String TAG = Cocos2dxGoogleAnalytics.class.getName();

        private static Activity sActivity = null;

        private static boolean mTrackUncaughtExceptions = false;
        private static int mDispatchInterval = 20;
        private static int mLogLevel = 0;
        
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
    	        		Tracker tracker = GoogleAnalytics.getInstance(getActivity()).getTracker(trackingId);
    	        		GoogleAnalytics.getInstance(getActivity()).setDefaultTracker(tracker);
    	        		
    	        		// uncaught exceptin
    	        		if (Cocos2dxGoogleAnalytics.mTrackUncaughtExceptions) {
    	        		      ExceptionReporter reporter = new ExceptionReporter(tracker, GAServiceManager.getInstance(),
    	        		    		  Thread.getDefaultUncaughtExceptionHandler(), getActivity());
    	        		      Thread.setDefaultUncaughtExceptionHandler(reporter);
    	        		}
    	        		
    	        		// dispatch period
    	        		GAServiceManager.getInstance().setLocalDispatchPeriod(Cocos2dxGoogleAnalytics.mDispatchInterval);
    	        		
    	        		// log level
    	        		LogLevel settingLevel = LogLevel.WARNING;
    	        		LogLevel[] levels = LogLevel.values();
    	        		for (LogLevel level : levels) {
    	        			if (level.ordinal() == Cocos2dxGoogleAnalytics.mLogLevel) {
    	        				settingLevel = level;
    	        			}
    	        		}
    	        		GoogleAnalytics.getInstance(getActivity()).getLogger().setLogLevel(settingLevel);
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
    	        		Tracker tracker = GoogleAnalytics.getInstance(getActivity()).getDefaultTracker();
    	        		tracker.send(MapBuilder.createAppView().set(Fields.SCREEN_NAME, screen).build());
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
    	        		Tracker tracker = GoogleAnalytics.getInstance(getActivity()).getDefaultTracker();
    	        		tracker.send(MapBuilder.createEvent(category, action, label, (long) value).build());
    				}
    			});
        	}
        }
}