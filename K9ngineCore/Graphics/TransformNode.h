#pragma once

#include "../Common/IObserver.h"
#include "../Common/TransformChangeEvent.h"
#include "../GameObject.h"
#include "../Handle.h"
#include "../Math/Transform.h"
#include "INode.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    class SceneGraph;
    class TransformNode :public INode {
    public:
      using GameObjectPtr = Memory::Handle<K9ngineCore::GameObject>;;
      using GameObjectConstPtr = Memory::Handle<const GameObject>;
      using GameObjectTransformChangeEvent = Common::TransformChangeEvent<GameObject>;
      using TransformObserverSubject = GameObjectTransformChangeEvent::Subject;
      using TransformObserverEventArg = GameObjectTransformChangeEvent::EventArg;

      static const GameObjectPtr NullGameObjectPtr;

      /********************************/
      /******* INNER CLASSES **********/

      class TransformChangeObserver :public Common::IObserver<TransformObserverSubject, TransformObserverEventArg>{
      public:
        explicit TransformChangeObserver(TransformNode*);
        ~TransformChangeObserver() override final;
        void update(const TransformObserverSubject&, const TransformObserverEventArg&) const override final;
      private:
        TransformNode* mNode;
      };

      /********************************/

      TransformNode(SceneGraph&, GameObjectPtr);
      ~TransformNode() override final;

      void accept(ISceneGraphVisitor&) override final;

      const K9Math::Transform getTransform() const;

    private:
    private:
      std::shared_ptr<TransformChangeObserver> mTransformChangeObserver;
      GameObjectPtr mGameObject;

    };
  }
}