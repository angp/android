#pragma once
/*
 *      Copyright (C) 2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <pthread.h>

#include <android/native_activity.h>

#include "IActivityHandler.h"
#include "IInputHandler.h"

#include "xbmc.h"

class CXBMCApp : public IActivityHandler, public IInputHandler
{
public:
  CXBMCApp(ANativeActivity *nativeActivity);
  virtual ~CXBMCApp();

  bool isValid() { return m_activity != NULL &&
                          m_state.platform != NULL &&
                          m_state.xbmcInitialize != NULL &&
                          m_state.xbmcRun != NULL; }

  ActivityResult onActivate();
  void onDeactivate();

  void onStart();
  void onResume();
  void onPause();
  void onStop();
  void onDestroy();

  void onSaveState(void **data, size_t *size);
  void onConfigurationChanged();
  void onLowMemory();

  void onCreateWindow(ANativeWindow* window);
  void onResizeWindow();
  void onDestroyWindow();
  void onGainFocus();
  void onLostFocus();

  bool onKeyboardEvent(AInputEvent* event);
  bool onTouchEvent(AInputEvent* event);

private:
  void run();
  void join();
  
  ANativeActivity *m_activity;

  typedef struct {
    pthread_t thread;
    pthread_mutex_t mutex;
    ActivityResult result;
    bool stopping;

    XBMC_PLATFORM* platform;
    XBMC_Initialize_t xbmcInitialize;
    XBMC_Run_t xbmcRun;
    XBMC_Stop_t xbmcStop;
    XBMC_Key_t xbmcKey;
    XBMC_Touch_t xbmcTouch;
    XBMC_TouchGestureCheck_t xbmcTouchGestureCheck;
    XBMC_TouchGesture_t xbmcTouchGesture;
  } State;

  State m_state;
  
  class Touch {
    public:
      Touch() { reset(); }
      
      void reset() { x = -1.0f; y = -1.0f; time = -1; }
      void copy(const Touch &other) { x = other.x; y = other.y; time = other.time; }
      
      float x;      // in pixels (With possible sub-pixels)
      float y;      // in pixels (With possible sub-pixels)
      int64_t time; // in nanoseconds
  };
  
  Touch m_touchDown;
  Touch m_touchMoveLast;
  int   m_touchGesture;
  bool  m_touchDownExecuted;
  bool  m_touchMoving;
};
