#include <memory>

#include "../K9Debug.h"

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

    RenderNode::RenderNode(RenderNode&& other) noexcept
      : INode{ std::move(other) }
      , mRenderingComponent{ std::move(other.mRenderingComponent) }
    {
      other.mRenderingComponent = RenderingComponentPtr::null();
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