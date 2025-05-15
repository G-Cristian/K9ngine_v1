#include "RenderNode.h"

#include "INode.h"
#include "RenderingComponent.h"
#include "SceneGraph.h"

namespace K9ngineCore {
  namespace K9Graphics {
    RenderNode::RenderNode(SceneGraph& sceneGraph, RenderingComponentConstPtr renderingComponent)
      : INode{ sceneGraph }
      , mRenderingComponent { renderingComponent }
    {
    }

    const RenderNode::RenderingComponentConstPtr RenderNode::getRenderingComponent() const
    {
      return mRenderingComponent;
    }
  }
}