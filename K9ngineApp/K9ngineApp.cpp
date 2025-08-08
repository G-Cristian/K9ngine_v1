// K9ngineApp.cpp : Define las funciones de la biblioteca estática.
//

#include "pch.h"
//#include "framework.h"

#if defined(_DEBUG) && defined(K9_DEBUG_MEMORY)

#include "vld.h"

//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW

//#include <crtdbg.h>
//#include <stdlib.h>

#endif // K9_DEBUG_MEMORY

#include "K9ngineApp.h"

#include <chrono>
#include <print>

#include "K9Debug.h"

#include "Graphics/Renderer.h"
#include "Handle.h"
#include "Windows/K9Window.h"
#include "Windows/K9WindowsManager.h"

namespace K9ngine {
  void K9ngineApp::run() {
    using namespace K9ngineCore;
    if (init()) {
      start();
    }
    else {
      LOG_ADD_TAB();
      LOG_ERROR("Error initing game.");
      LOG_REMOVE_TAB();
    }

    cleanup();
  }

  float K9ngineApp::getCurrentTime() {
    using namespace std::chrono;

    return static_cast<float>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
  }

  bool K9ngineApp::init() {
    using namespace K9ngineCore;
    using namespace K9ngineCore::K9Graphics;
    LOG_ADD_TAB();

    bool ok = mWindowsManager.init();
    if (ok) {
      mWindowsManager.createWindow("Test Game", 600, 600);
      mWindowsManager.setCurrent(0);

      int version = GraphicsContext::init();
      if (version == 0) {
        LOG_ERROR("OpenGLWrapper::init() == 0");
      }
      else {
        mWindowsManager.setSwapInterval();
        mWindowsManager.currentWindow().init();
      }
    }

    GraphicsContext::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    LOG_REMOVE_TAB();

    return ok;
  }

  void K9ngineApp::start() {
    float previous = getCurrentTime();
    float lag = 0.0;
    float current = 0.0;
    float elapsed = 0.0;
    while (!mMustClose) {
      current = getCurrentTime();
      elapsed = current - previous;
      previous = current;
      lag += elapsed;

      processInput();

      while (lag >= mMsPerFixedUpdate) {
        fixedUpdate();
        fixedPhysics();
        lag -= mMsPerFixedUpdate;
      }

      update(elapsed);
      render(elapsed);
    }
  }

  void K9ngineApp::processInput() {
    // TODO: Update keyboard and mouse objects with current values.
  }

  void K9ngineApp::fixedUpdate() {
    // TODO: Update fixed scripts engine (mMsPerFixedUpdate) which must call every fixedUpdate scripts
  }

  void K9ngineApp::fixedPhysics() {
    // TODO: Update physics engine (mMsPerFixedUpdate) (besides updating physics will call the corresponding OnCollision events)
  }

  void K9ngineApp::update(float elapsed) {
    // TODO: Update scripts engine (elapsed) which must call every update scripts
    mMustClose = mMustClose || mWindowsManager.currentWindow().shouldClose();
  }

  void K9ngineApp::render(float elapsed) {
    // TODO: Update rendering engine (elapsed)
    mRenderer.render(elapsed);
    mWindowsManager.update();
  }

  void K9ngineApp::cleanup() {
    mWorld.clear();
    mRenderer.clear();
    mWindowsManager.destroyAll();
    //mWindowsManager.terminate();
    mSettingsFullPath = nullptr;
  }
}