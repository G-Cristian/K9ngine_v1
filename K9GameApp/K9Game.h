#ifndef K9_GAME_H
#define K9_GAME_H

namespace K9ngineGame {
  class K9Game {
  public:
    explicit K9Game(const char* settingsFullpath = "K9ngineSettings.txt") :
        mMsPerFixedUpdate(16.0)   // 1000 ms/60 fs = 16.66 ms per frame
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

    double getCurrentTime();

    void init();
    void start();

    void processInput();
    void fixedUpdate();
    void fixedPhysics();
    void update(double elapsed);
    void render(double elapsed);

    void cleanup();

    double mMsPerFixedUpdate;
    const char* mSettingsFullPath;
    bool mMustClose;
  };
}

#endif // !K9_GAME_H
