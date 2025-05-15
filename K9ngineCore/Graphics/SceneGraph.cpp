#include "SceneGraph.h"

#include "ISceneGraphVisitor.h"
#include "Renderer.h"
#include "TransformNode.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    SceneGraph::SceneGraph()
      :mRoot{std::make_shared<TransformNode>(*this, TransformNode::NullGameObjectPtr)}
    {

    }

    void SceneGraph::cleanDirty(INode* node)
    {
      K9ASSERT(node, "node is null");
      node->cleanDirty();
    }

    void SceneGraph::propagateDirtyUpwards()
    {
      while (!mDirtyNodes.empty()) {
        propagateDirtyUpwards(mDirtyNodes.front());
        mDirtyNodes.pop();
      }
    }

    void SceneGraph::propagateDirtyUpwards(INode* node)
    {
      if (node->isDirty()) {
        if (!node->getParent()->isDirty()) {
          setDirty(node->getParent().get());
        }
      }
    }

    void SceneGraph::accept(ISceneGraphVisitor& visitor)
    {
      mRoot->accept(visitor);
    }

    void SceneGraph::setDirty(INode* node)
    {
      K9ASSERT(node, "node is null");
      if (!node->isDirty()) {
        node->setDirty();
        mDirtyNodes.push(node);
      }
    }
  }
}