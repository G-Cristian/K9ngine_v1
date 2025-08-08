#include <memory>

#include "ISceneGraphVisitor.h"

namespace K9ngineCore {
  namespace K9Graphics {
    ISceneGraphVisitor::ISceneGraphVisitor(SceneGraph& sceneGraph)
      :mSceneGraph{sceneGraph}
    {
    }

    ISceneGraphVisitor::~ISceneGraphVisitor()
    {
    }
  }
}