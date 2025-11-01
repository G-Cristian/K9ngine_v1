#ifndef K9_GAME_H
#define K9_GAME_H

#include "GameObject.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/TransformNode.h"
#include "Handle.h"
#include "../K9ngineApp/Windows/K9WindowsManager.h"

namespace K9ngineGame {
  class K9Game {
  public:
    explicit K9Game(const char* settingsFullpath = "K9ngineSettings.txt") :
        mRenderer{}
      , mWindowsManager(4, 3)
      , mMsPerFixedUpdate(16.0)   // 1000 ms/60 fs = 16.66 ms per frame
      , mSettingsFullPath(settingsFullpath)
      , mMustClose(false)
    {}
    ~K9Game() = default;
    void run();

    void CloseGame() { mMustClose = true; }
  private:
    K9Game(const K9Game&) = delete;
    K9Game(K9Game&&) noexcept = delete;
    K9Game& operator=(const K9Game&) = delete;
    K9Game& operator=(K9Game&&) noexcept = delete;

    float getCurrentTime();

    bool init();
    void start();

    void processInput();
    void fixedUpdate();
    void fixedPhysics();
    void update(float elapsed);
    void render(float elapsed);

    void cleanup();

    K9ngineCore::K9Graphics::Renderer mRenderer;
    K9ngine::K9Windows::K9WindowsManager mWindowsManager;
    float mMsPerFixedUpdate;
    const char* mSettingsFullPath;
    bool mMustClose;
  };
}

#endif // !K9_GAME_H
