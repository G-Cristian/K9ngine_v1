#include "K9Window.h"

#include "../../K9ngineCore/K9Debug.h"
#include "../../K9ngineCore/Logger.h"

#include <functional>

namespace K9ngine {
  namespace K9Windows {
    K9Window::K9Window(const std::string& title, int width, int height) :
      K9Window(title, width, height, std::hash<std::string>()(std::format("{}_{}_{}", title, width, height)))
    {
    }

    K9Window::K9Window(const std::string& title, int width, int height, size_t id) :
        mTitle(title)
      , mWindow(nullptr)
      , mId{id}
      , mWidth(width)
      , mHeight(height)
    {
      using namespace K9ngineCore;
      mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
      if (mWindow) {
        glfwSetWindowUserPointer(mWindow, this);
        glfwSetWindowSizeCallback(mWindow, &K9Window::onSetWindowSizeCallback);
        glfwSetFramebufferSizeCallback(mWindow, &K9Window::onSetFramebufferSizeCallback);
      }
      K9ASSERT(!!(mWindow), "Window is null");
    }

    K9Window::K9Window(K9Window&& other) noexcept
      : mWindowSizeChangeObserver{std::move(other.mWindowSizeChangeObserver)}
      , mFramebufferSizeChangeObserver{std::move(other.mFramebufferSizeChangeObserver)}
      , mTitle{ std::move(other.mTitle) }
      , mWindow{other.mWindow}
      , mId{other.mId}
      , mWidth{other.mWidth}
      , mHeight{other.mHeight}
    {
      other.mWindow = nullptr;
      if (mWindow) {
        glfwSetWindowUserPointer(mWindow, this);
      }
    }

    K9Window& K9Window::operator=(K9Window&& rho) noexcept {
      if (this != &rho) {
        destroy();

        mWindowSizeChangeObserver = std::move(rho.mWindowSizeChangeObserver);
        mFramebufferSizeChangeObserver = std::move(rho.mFramebufferSizeChangeObserver);
        mTitle = std::move(rho.mTitle);
        mId = rho.mId;
        mWidth = rho.mWidth;
        mHeight = rho.mHeight;

        mWindow = rho.mWindow;
        
        rho.mWindow = nullptr;
        if (mWindow) {
          glfwSetWindowUserPointer(mWindow, this);
        }
      }

      return *this;
    }

    K9Window::~K9Window() {
      destroy();
    }

    void K9Window::init() const {
      // TODO
    }

    bool K9Window::shouldClose() const
    {
      using namespace K9ngineCore;
      K9ASSERT(!!(mWindow), "Window is null");
      return glfwWindowShouldClose(mWindow);
    }

    K9Window::Size K9Window::getFramebufferSize() const
    {
      using namespace K9ngineCore;
      K9ASSERT(!!(mWindow), "Window is null");
      int width{};
      int height{};
      glfwGetFramebufferSize(mWindow, &width, &height);

      return Size{ width, height };
    }

    size_t K9Window::getId() const {
      return mId;
    }

    void K9Window::swapBuffers() const
    {
      using namespace K9ngineCore;
      K9ASSERT(!!(mWindow), "Window is null");
      glfwSwapBuffers(mWindow);
    }

    void K9Window::destroy()
    {
      mWindowSizeChangeObserver.clear();
      mFramebufferSizeChangeObserver.clear();
      if (mWindow) {
        glfwSetWindowUserPointer(mWindow, nullptr);
        glfwSetWindowSizeCallback(mWindow, nullptr);
        glfwSetFramebufferSizeCallback(mWindow, nullptr);
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
      }
    }

    void K9Window::addWindowSizeChangeObserver(std::shared_ptr<IWindowSizeChangeObserber> observer)
    {
      mWindowSizeChangeObserver.push_back(observer);
    }

    void K9Window::addFramebufferSizeChangeObserver(std::shared_ptr<IFramebufferSizeChangeObserber> observer)
    {
      mFramebufferSizeChangeObserver.push_back(observer);
    }

    void K9Window::onSetWindowSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
    {
      auto* k9Window = static_cast<K9Window*>(glfwGetWindowUserPointer(window));
      if (k9Window) {
        k9Window->onSetWindowSize(newWidth, newHeight);
      }
    }

    void K9Window::onSetFramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
    {
      auto* k9Window = static_cast<K9Window*>(glfwGetWindowUserPointer(window));
      if (k9Window) {
        k9Window->onSetFramebufferSize(newWidth, newHeight);
      }
    }

    void K9Window::onSetWindowSize(int width, int height)
    {
      for(auto observer : mWindowSizeChangeObserver)
      {
        observer->update(width, height);
      }
    }

    void K9Window::onSetFramebufferSize(int width, int height)
    {
      for (auto observer : mFramebufferSizeChangeObserver)
      {
        observer->update(width, height);
      }
    }

    void K9Window::makeContextCurrent() const
    {
      using namespace K9ngineCore;
      K9ASSERT(!!(mWindow), "Window is null");
      glfwMakeContextCurrent(mWindow);
    }
  }
}