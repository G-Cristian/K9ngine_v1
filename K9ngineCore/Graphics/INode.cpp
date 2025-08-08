#include <memory>

#include "INode.h"

#include "SceneGraph.h"

namespace K9ngineCore {
  namespace K9Graphics {
    INode::INode(SceneGraph& sceneGraph)
      : mSceneGraph{ sceneGraph }
    {
    }

    INode::~INode()
    {
      //mParent = nullptr;
      // Clean up children
      for (auto& child : mChildren) {
        child->setParent(nullptr);
        child = nullptr;
      }

      mChildren.clear();
      mChildren.shrink_to_fit();
    }

    const SceneGraph& INode::getSceneGraph() const
    {
      return mSceneGraph;
    }

    SceneGraph& INode::getSceneGraph()
    {
      return mSceneGraph;
    }

    bool INode::isDirty() const
    {
      return mIsDirty;
    }

    const INode::NodePtr INode::getParent() const
    {
      return mParent.lock();
    }

    INode::NodePtr INode::getParent()
    {
      return mParent.lock();
    }

    const std::vector<INode::NodePtr>& INode::getChildren() const
    {
      return mChildren;
    }

    void INode::cleanDirty() {
      mIsDirty = false;
    }

    void INode::setDirty()
    {
      mIsDirty = true;
    }

    void INode::addChild(NodePtr child)
    {
      mChildren.push_back(child);
    }

    void INode::setParent(NodePtr parent)
    {
      mParent = parent;
    }
  }
}