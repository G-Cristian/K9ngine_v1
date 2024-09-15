#include "K9WindowsManager.h"

#include "K9Debug.h"

#include <GLFW/glfw3.h>

using namespace K9ngineCore;

namespace K9ngineGame {
  K9WindowsManager::K9WindowsManager(int contextVersionMajor /*= 4*/, int contextVersionMinor /*= 3*/) noexcept:
    mWindows()
  , mCurrentWindowIndex(-1)
  , mSwapInterval(1)
  , mContextVersionMajor(contextVersionMajor)
  , mContextVersionMinor(contextVersionMinor) 
  {}

  K9WindowsManager::~K9WindowsManager() {
    destroyAll();
    terminate();
  }

  K9Window& K9WindowsManager::createWindow(const std::string& title, int width, int height) {
    mWindows.emplace_back(title, width, height);
    return mWindows.back();
  }

  K9Window& K9WindowsManager::setCurrent(int index) {
    K9ASSERT(!!(index >= 0 && index < mWindows.size()), "window index out of range");

    mCurrentWindowIndex = index;
    auto& current = mWindows[index];
    current.makeContextCurrent();

    return current;
  }

  void K9WindowsManager::setSwapInterval(int swapInterval /*= 1*/) {
    mSwapInterval = swapInterval;
    glfwSwapInterval(swapInterval);
  }

  K9Window& K9WindowsManager::currentWindow() {
    K9ASSERT(!!(mCurrentWindowIndex >= 0 && mCurrentWindowIndex < mWindows.size()), "mCurrentWindowIndex out of range");
    return mWindows[mCurrentWindowIndex];
  }

  const K9Window& K9WindowsManager::currentWindow() const {
    K9ASSERT(!!(mCurrentWindowIndex >= 0 && mCurrentWindowIndex < mWindows.size()), "mCurrentWindowIndex out of range");
    return mWindows[mCurrentWindowIndex];
  }

  inline int K9WindowsManager::size() const {
    return mWindows.size();
  }

  bool K9WindowsManager::init() const{
    if (!glfwInit()) {
      LOG_ADD_TAB();
      LOG_ERROR("glfwInit() returned false.");
      LOG_REMOVE_TAB();

      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mContextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mContextVersionMinor);

    return true;
  }

  void K9WindowsManager::update() const{
    currentWindow().swapBuffers();
    glfwPollEvents();
  }

  void K9WindowsManager::destroyAll() {
    for (auto& window : mWindows) {
      window.destroy();
    }

    mWindows.clear();
  }

  inline void K9WindowsManager::terminate() const {
    glfwTerminate();
  }
}