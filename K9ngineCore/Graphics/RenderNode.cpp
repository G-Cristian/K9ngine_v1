#include "RenderNode.h"

#include "INode.h"
#include "ISceneGraphVisitor.h"
#include "RenderingComponent.h"
#include "SceneGraph.h"

namespace K9ngineCore {
  namespace K9Graphics {
    RenderNode::RenderNode(SceneGraph& sceneGraph, RenderingComponentPtr renderingComponent)
      : INode{ sceneGraph }
      , mRenderingComponent { renderingComponent }
    {
    }


    void RenderNode::accept(ISceneGraphVisitor& visitor)
    {
      visitor.visit(*this);
    }

    const RenderingComponentPtr RenderNode::getRenderingComponent() const
    {
      return mRenderingComponent;
    }
  }
}