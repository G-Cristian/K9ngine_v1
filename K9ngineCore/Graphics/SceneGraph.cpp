#include "SceneGraph.h"


#include "Camera.h"
#include "CommonHandleTypes.h"
#include "GraphicsHandleTypes.h"
#include "ISceneGraphVisitor.h"
#include "Renderer.h"
#include "RenderingComponent.h"
#include "RenderNode.h"
#include "TransformNode.h"

#include "../Common//Hasher.h"

#include <cstdint>
#include <format>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    SceneGraph::SceneGraph()
      : mCurrentCamera{nullptr}
      , mRoot{std::make_shared<TransformNode>(*this, TransformNode::NullGameObjectPtr)}
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

    std::shared_ptr<TransformNode> SceneGraph::createOrGetTransformNode(GameObjectPtr gameObject)
    {
      std::shared_ptr<TransformNode> transformNode{ nullptr };

      if (!mGameObjectIdTransformNode.contains(gameObject->getId())) {
        mGameObjectIdTransformNode[gameObject->getId()] = transformNode = std::make_shared<TransformNode>(*this, gameObject);
        auto parentTransformationNode = mRoot;
        // TODO: When I add nested game objects I will have to look for the parent's game object's transformation node in the scene graph (mGameObjectIdTransformNode)
        //       and set parentTransformationNode to it

        linkNode(transformNode, parentTransformationNode);
      }
      else {
        transformNode = mGameObjectIdTransformNode[gameObject->getId()];
      }

      return transformNode;
    }

    std::shared_ptr<RenderNode> SceneGraph::createRenderNode(RenderingComponentPtr renderingComponent)
    {
      return std::make_shared<RenderNode>(*this, renderingComponent);
    }

    std::shared_ptr<INode> SceneGraph::linkNode(std::shared_ptr<INode> node, std::shared_ptr<INode> parent)
    {
      auto realParent = parent ? parent : mRoot;
      node->setParent(realParent);
      realParent->addChild(node);

      return realParent;
    }

    std::shared_ptr<Camera> SceneGraph::setCurrentCamera(std::shared_ptr<Camera> camera)
    {
      mCurrentCamera = camera;
      return mCurrentCamera;
    }

    std::shared_ptr<Camera> SceneGraph::getCurrentCamera()
    {
      return mCurrentCamera;
    }

    std::shared_ptr<const Camera> SceneGraph::getCurrentCamera() const
    {
      return mCurrentCamera;
    }
  }
}