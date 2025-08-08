#ifndef K9_GAME_H
#define K9_GAME_H

#include <memory>

#include "../K9ngineCore/Graphics/GraphicsContext.h"

#include "Windows/K9WindowsManager.h"

#include "../K9ngineCore/GameObject.h"
#include "../K9ngineCore/Graphics/Camera.h"
#include "../K9ngineCore/Graphics/Renderer.h"
#include "../K9ngineCore/Graphics/TransformNode.h"
#include "../K9ngineCore/Handle.h"
#include "../K9ngineCore/World.h"

namespace K9ngine {
  class K9ngineApp {
  public:
    //const char* settingsFullpath = "K9ngineSettings.txt"
    explicit K9ngineApp(const char* settingsFullpath) :
        mRenderer{}
      , mWindowsManager(4, 3)
      , mMsPerFixedUpdate(16.0)   // 1000 ms/60 fs = 16.66 ms per frame
      , mSettingsFullPath(settingsFullpath)
      , mMustClose(false)
    {}

    explicit K9ngineApp(int contextVersionMajor = 4, int contextVersionMinor = 3, float msPerFrame = 16.0) :
        mRenderer{}
      , mWindowsManager{ contextVersionMajor, contextVersionMinor }
      , mMsPerFixedUpdate{ msPerFrame }
      , mSettingsFullPath(nullptr)
      , mMustClose(false)
    {
    }

    virtual ~K9ngineApp() = default;

    void run();

    void CloseGame() { mMustClose = true; }
  private:
    K9ngineApp(const K9ngineApp&) = delete;
    K9ngineApp(K9ngineApp&&) noexcept = delete;
    K9ngineApp& operator=(const K9ngineApp&) = delete;
    K9ngineApp& operator=(K9ngineApp&&) noexcept = delete;
  protected:
    float getCurrentTime();

    virtual bool init();
    void start();

    virtual void processInput();
    virtual void fixedUpdate();
    virtual void fixedPhysics();
    virtual void update(float elapsed);
    virtual void render(float elapsed);

    virtual void cleanup();

    K9ngineCore::World mWorld;
    K9ngineCore::K9Graphics::Renderer mRenderer;
    K9ngineCore::K9Windows::K9WindowsManager mWindowsManager;
    float mMsPerFixedUpdate;
    const char* mSettingsFullPath;
    bool mMustClose;
  };
}

#endif // !K9_GAME_H
