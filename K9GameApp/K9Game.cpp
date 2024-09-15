#include "K9Game.h"

#include "K9Debug.h"
#include "K9Window.h"
#include "K9WindowsManager.h"

#include <chrono>

namespace K9ngineGame {

  void K9Game::run() {
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

  double K9Game::getCurrentTime() {
    using namespace std::chrono;

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  }

  bool K9Game::init() {
    using namespace K9ngineCore;
    LOG_ADD_TAB();
    // TODO: Init settings.
    // TODO: Init necessary stuff.
    bool ok = mWindowsManager.init();
    if (ok) {
      mWindowsManager.createWindow("Test Game", 600, 600);
      mWindowsManager.setCurrent(0);

      int version = OpenGLWrapper::init();
      if (version == 0) {
        LOG_ERROR("OpenGLWrapper::init() == 0");
      }
      else {
        mWindowsManager.setSwapInterval();
        mWindowsManager.currentWindow().init();
      }
    }

    LOG_REMOVE_TAB();

    return ok;
  }

  void K9Game::start() {
    double previous = getCurrentTime();
    double lag = 0.0;
    double current = 0.0;
    double elapsed = 0.0;
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

  void K9Game::processInput() {
    // TODO: Update keyboard and mouse objects with current values.
  }

  void K9Game::fixedUpdate() {
    // TODO: Update fixed scripts engine (mMsPerFixedUpdate) which must call every fixedUpdate scripts
  }

  void K9Game::fixedPhysics() {
    // TODO: Update physics engine (mMsPerFixedUpdate) (besides updating physics will call the corresponding OnCollision events)
  }

  void K9Game::update(double elapsed) {
    // TODO: Update scripts engine (elapsed) which must call every update scripts
    mMustClose = mMustClose || mWindowsManager.currentWindow().shouldClose();
  }

  void K9Game::render(double elapsed) {
    // TODO: Update rendering engine (elapsed)
    mWindowsManager.update();
  }

  void K9Game::cleanup() {
    // TODO: Do necessary cleanup.
    
    mWindowsManager.destroyAll();
  }
}