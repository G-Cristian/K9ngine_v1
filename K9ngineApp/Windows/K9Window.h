#ifndef K9WINDOW_H_
#define K9WINDOW_H_

#include "GLFW/glfw3.h"

#include "WindowObservers.h"

#include <memory>
#include <string>
#include <vector>

namespace K9ngine {
  namespace K9Windows {
    class K9Window {
      friend class K9WindowsManager;
    public:
      struct Size
      {
        int width;
        int height;
      };

      explicit K9Window(const std::string&, int, int);
      explicit K9Window(const std::string&, int, int, size_t);
      K9Window(K9Window&&) noexcept;
      K9Window& operator=(K9Window&&) noexcept;

      ~K9Window();

      void init() const;
      bool shouldClose() const;

      Size getFramebufferSize() const;
      size_t getId() const;

      void swapBuffers() const;
      void destroy();

      void addWindowSizeChangeObserver(std::shared_ptr<IWindowSizeChangeObserber>);
      void addFramebufferSizeChangeObserver(std::shared_ptr<IFramebufferSizeChangeObserber>);

      static void onSetWindowSizeCallback(GLFWwindow*, int, int);
      static void onSetFramebufferSizeCallback(GLFWwindow*, int, int);

    private:
      K9Window(const K9Window&) = delete;
      K9Window& operator=(const K9Window&) = delete;

      void makeContextCurrent() const;

      void onSetWindowSize(int, int);
      void onSetFramebufferSize(int, int);
    private:
      std::vector<std::shared_ptr<IWindowSizeChangeObserber>> mWindowSizeChangeObserver{};
      std::vector<std::shared_ptr<IFramebufferSizeChangeObserber>> mFramebufferSizeChangeObserver{};
      std::string mTitle;
      GLFWwindow* mWindow;
      size_t mId;
      int mWidth;
      int mHeight;
    };
  }
}

#endif // !K9WINDOW_H_
