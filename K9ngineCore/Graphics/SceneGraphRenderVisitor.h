#pragma once

#include "../Math/Math.h"
#include "ISceneGraphVisitor.h"

#include <memory>
#include <stack>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class RenderNode;
    class RenderingItem;
    class SceneGraph;
    class TransformNode;

    class SceneGraphRenderVisitor :public ISceneGraphVisitor
    {
    public:
      SceneGraphRenderVisitor(SceneGraph&);

      void visit(RenderNode&) override final;
      void visit(TransformNode&) override final;

      std::shared_ptr<std::vector<std::shared_ptr<RenderingItem>>> getRenderingItems() const;
    private:
      std::stack<K9Math::Mat4> mTransforms{};
      std::shared_ptr<std::vector<std::shared_ptr<RenderingItem>>> mRenderingItems;
    };
  }
}