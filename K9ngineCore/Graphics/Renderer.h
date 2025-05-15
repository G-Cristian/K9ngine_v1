#pragma once

#include "SceneGraph.h"
#include <memory>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class RenderingItem;

    class Renderer {
    public:
      Renderer() = default;

      void render(float elapsedTime);
    private:
      SceneGraph mScene;
    };
  }
}