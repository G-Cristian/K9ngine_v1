#ifndef K9WINDOW_H_
#define K9WINDOW_H_

#include "GLFW/glfw3.h"

#include <string>

namespace K9ngineGame {
  class K9Window {
    friend class K9WindowsManager;
  public:
    explicit K9Window(const std::string&, int, int);
    K9Window(K9Window&&) noexcept = default;
    K9Window& operator=(K9Window&&) noexcept = default;

    ~K9Window();

    void init() const;
    bool shouldClose() const;

    void swapBuffers() const;
    void destroy();

  private:
    K9Window(const K9Window&) = delete;
    K9Window& operator=(const K9Window&) = delete;

    void makeContextCurrent() const;
  private:
    std::string mTitle;
    GLFWwindow* mWindow;
    int mWidth;
    int mHeight;
  };
}

#endif // !K9WINDOW_H_
