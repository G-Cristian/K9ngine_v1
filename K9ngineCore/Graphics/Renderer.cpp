#include "Renderer.h"

#include "ISceneGraphVisitor.h"
#include "RenderingItem.h"
#include "SceneGraph.h"
#include "SceneGraphRenderVisitor.h"

#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    void Renderer::render(float elapsedTime)
    {
      SceneGraphRenderVisitor sceneGraphVisitor{ mScene };
      mScene.accept(sceneGraphVisitor);
      auto renderingItems = sceneGraphVisitor.getRenderingItems();
      // TODO: sort renderingItems as apropriate
      // TODO: render the renderingItems.
    }
  }
}