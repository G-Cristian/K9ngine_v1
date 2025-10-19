#pragma once

#include <memory>

#include "../K9ngineCore/K9Debug.h"

#include "../K9ngineCore/World.h"
#include "../K9ngineCore/Graphics/Renderer.h"
#include "../K9ngineCore/Graphics/PerspectiveCamera.h"

#include "../K9ngineApp/K9ngineApp.h"

namespace K9ngineAppTest
{
  using namespace K9ngineCore;
  class TestInstanced1 : public K9ngine::K9ngineApp
  {
  public:
    //const char* settingsFullpath = "K9ngineSettings.txt"
    explicit TestInstanced1(const char* settingsFullpath) :
      K9ngine::K9ngineApp{ settingsFullpath }
    {
    }

    explicit TestInstanced1(int contextVersionMajor = 4, int contextVersionMinor = 3, float msPerFrame = 16.0) :
      K9ngine::K9ngineApp{ contextVersionMajor, contextVersionMinor, msPerFrame }
    {
    }

    ~TestInstanced1() override = default;
  private:
    bool init() override;
    void update(double elapsed) override;
  };
}
