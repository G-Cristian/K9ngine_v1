#include "K9Game.h"

#include <chrono>

namespace K9ngineGame {

  void K9Game::run() {
    init();
    start();
    cleanup();
  }

  double K9Game::getCurrentTime() {
    using namespace std::chrono;

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  }

  void K9Game::init() {
    // TODO: Init settings.
    // TODO: Init necessary stuff.
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
  }

  void K9Game::render(double elapsed) {
    // TODO: Update rendering engine (elapsed)
  }

  void K9Game::cleanup() {
    // TODO: Do necessary cleanup.
  }
}