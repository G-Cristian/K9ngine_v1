#include "TransformNode.h"

#include "../GameObject.h"
#include "../Handle.h"
#include "../Math/Transform.h"

#include "INode.h"
#include "ISceneGraphVisitor.h"
#include "SceneGraph.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    const TransformNode::GameObjectPtr TransformNode::NullGameObjectPtr = Memory::HandleTable<K9ngineCore::GameObject>::NullHandle;

    TransformNode::TransformChangeObserver::TransformChangeObserver(TransformNode* node)
      : Common::IObserver<TransformObserverSubject, TransformObserverEventArg>{}
      , mNode{node}
    {
    }

    TransformNode::TransformChangeObserver::~TransformChangeObserver()
    {
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
      if (mGameObject != NullGameObjectPtr) {
        mGameObject->addObserver(mTransformChangeObserver);
      }
    }

    TransformNode::~TransformNode()
    {

    }

    void TransformNode::accept(ISceneGraphVisitor& visitor) 
    {
      visitor.visit(*this);
    }

    const K9Math::Transform& TransformNode::getTransform() const {
      if (mGameObject != NullGameObjectPtr) {
        return mGameObject->getTransform();
      }
    }
  }
}