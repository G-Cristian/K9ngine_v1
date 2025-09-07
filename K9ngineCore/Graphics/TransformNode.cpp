#include <memory>

#include "../K9Debug.h"

#include "TransformNode.h"

#include "../GameObject.h"
#include "../Handle.h"
#include "../Math/Transform.h"

#include "INode.h"
#include "ISceneGraphVisitor.h"
#include "SceneGraph.h"

namespace K9ngineCore {
  namespace K9Graphics {
    const GameObjectPtr TransformNode::NullGameObjectPtr = Memory::HandleTable<K9ngineCore::GameObject>::NullHandle;

    TransformNode::TransformChangeObserver::TransformChangeObserver(TransformNode* node)
      : Common::IObserver<TransformObserverSubject, TransformObserverEventArg>{}
      , mNode{node}
    {
    }

    TransformNode::TransformChangeObserver::TransformChangeObserver(TransformChangeObserver&& other) noexcept
      : Common::IObserver<TransformObserverSubject, TransformObserverEventArg>{}
      , mNode{ other.mNode }
    {
      other.mNode = nullptr;
    }

    TransformNode::TransformChangeObserver::~TransformChangeObserver()
    {
      mNode = nullptr;
    }

    TransformNode::TransformChangeObserver& TransformNode::TransformChangeObserver::operator=(TransformChangeObserver&& other) noexcept
    {
      if (this != &other) {
        Common::IObserver<TransformObserverSubject, TransformObserverEventArg>::operator=(std::move(other));
        mNode = other.mNode;

        other.mNode = nullptr;
      }

      return *this;
    }

    void TransformNode::TransformChangeObserver::update(const TransformObserverSubject& subject, const TransformObserverEventArg& args) const
    {
      mNode->getSceneGraph().setDirty(mNode);
    }

    TransformNode::TransformNode(SceneGraph& scene, GameObjectPtr gameObject)
      : INode{ scene }
      , mTransformChangeObserver{ std::make_shared<TransformChangeObserver>(this) }
      , mGameObject{gameObject}
    {
      if (mGameObject.isValid()) {
        mGameObject->addObserver(mTransformChangeObserver);
      }
    }

    TransformNode::~TransformNode()
    {
      if (mGameObject) {
        mGameObject->removeObserver(mTransformChangeObserver);
      }

      mTransformChangeObserver = nullptr;
    }

    void TransformNode::accept(ISceneGraphVisitor& visitor) 
    {
      visitor.visit(*this);
    }

    const K9Math::Transform TransformNode::getTransform() const {
      return mGameObject.isValid() ? mGameObject->getTransform() : K9Math::Transform::identity();
    }
  }
}