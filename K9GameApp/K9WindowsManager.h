#ifndef K9WINDOWSMANAGER_H_
#define K9WINDOWSMANAGER_H_

#include "K9Window.h"

#include <string>
#include <vector>

namespace K9ngineGame {
  class K9WindowsManager {
  public:
    explicit K9WindowsManager(int contextVersionMajor = 4, int contextVersionMinor = 3) noexcept;
    ~K9WindowsManager();

    K9Window& createWindow(char const* const title, int width, int height) { return createWindow(std::string(title), width, height); }
    K9Window& createWindow(const std::string&, int, int);

    K9Window& setCurrent(int index);
    void setSwapInterval(int swapInterval = 1);

    K9Window& currentWindow();
    const K9Window& currentWindow() const;
    inline int size() const;

    bool init() const;
    void update() const;

    void destroyAll();
  private:
    K9WindowsManager(const K9WindowsManager&) = delete;
    K9WindowsManager(K9WindowsManager&&) noexcept = delete;
    K9WindowsManager& operator=(const K9WindowsManager&) = delete;
    K9WindowsManager& operator=(K9WindowsManager&&) noexcept = delete;

    inline void terminate() const;
  private:
    std::vector<K9Window> mWindows;
    int mCurrentWindowIndex;
    int mSwapInterval;
    int mContextVersionMajor;
    int mContextVersionMinor;
  };
}

#endif // !K9WINDOWMANAGER_H_
