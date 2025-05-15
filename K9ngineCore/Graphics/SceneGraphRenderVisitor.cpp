#include "SceneGraphRenderVisitor.h"

#include "ISceneGraphVisitor.h"
#include "RenderNode.h"
#include "RenderingItem.h"
#include "SceneGraph.h"
#include "TransformNode.h"

#include <memory>
#include <stack>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    SceneGraphRenderVisitor::SceneGraphRenderVisitor(SceneGraph& sceneGraph)
      : ISceneGraphVisitor(sceneGraph)
      , mRenderingItems{ std::make_shared<std::vector<std::shared_ptr<RenderingItem>>>() }
    {
      mTransforms.push(K9Math::Transform::identity().getTransformMat4());
    }

    void SceneGraphRenderVisitor::visit(RenderNode& node)
    {
      mRenderingItems->push_back(std::make_shared<RenderingItem>(node.getRenderingComponent(), mTransforms.top()));

      for (const auto child : node.getChildren()) {
        child->accept(*this);
      }
    }
    
    void SceneGraphRenderVisitor::visit(TransformNode& node)
    {
      mTransforms.push(mTransforms.top() * node.getTransform().getTransformMat4());

      mSceneGraph.cleanDirty(&node);
      for (const auto child : node.getChildren()) {
        child->accept(*this);
      }
      mTransforms.pop();
    }

    std::shared_ptr<std::vector<std::shared_ptr<RenderingItem>>> SceneGraphRenderVisitor::getRenderingItems() const
    {
      return mRenderingItems;
    }
  }
}