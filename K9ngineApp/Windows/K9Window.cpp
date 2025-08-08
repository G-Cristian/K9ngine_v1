#include "K9Window.h"

#include "../../K9ngineCore/K9Debug.h"
#include "../../K9ngineCore/Logger.h"

namespace K9ngineCore {
  namespace K9Windows {
    K9Window::K9Window(const std::string& title, int width, int height) :
      mTitle(title)
      , mWindow(nullptr)
      , mWidth(width)
      , mHeight(height)
    {
      mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
      K9ASSERT(!!(mWindow), "Window is null");
    }

    K9Window::~K9Window() {
      destroy();
    }

    void K9Window::init() const {
      // TODO
    }

    bool K9Window::shouldClose() const {
      K9ASSERT(!!(mWindow), "Window is null");
      return glfwWindowShouldClose(mWindow);
    }

    K9Window::Size K9Window::getFramebufferSize() const
    {
      K9ASSERT(!!(mWindow), "Window is null");
      int width{};
      int height{};
      glfwGetFramebufferSize(mWindow, &width, &height);

      return Size{ width, height };
    }

    void K9Window::swapBuffers() const {
      K9ASSERT(!!(mWindow), "Window is null");
      glfwSwapBuffers(mWindow);
    }

    void K9Window::destroy() {
      if (mWindow) {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
      }
    }

    void K9Window::makeContextCurrent() const {
      K9ASSERT(!!(mWindow), "Window is null");
      glfwMakeContextCurrent(mWindow);
    }
  }
}