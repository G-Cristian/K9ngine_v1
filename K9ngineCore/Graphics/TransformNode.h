#pragma once

#include <memory>

#include "../Common/IObserver.h"
#include "../Common/TransformChangeEvent.h"
#include "../CommonHandleTypes.h"
#include "../GameObject.h"
#include "../Handle.h"
#include "../Math/Transform.h"
#include "INode.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class ISceneGraphVisitor;
    class SceneGraph;

    class TransformNode :public INode {
    public:
      using GameObjectTransformChangeEvent = Common::TransformChangeEvent<GameObject>;
      using TransformObserverSubject = GameObjectTransformChangeEvent::Subject;
      using TransformObserverEventArg = GameObjectTransformChangeEvent::EventArg;

      static const GameObjectPtr NullGameObjectPtr;

      /********************************/
      /******* INNER CLASSES **********/

      class TransformChangeObserver :public Common::IObserver<TransformObserverSubject, TransformObserverEventArg>{
      public:
        explicit TransformChangeObserver(TransformNode*);
        
        TransformChangeObserver(TransformChangeObserver&&) noexcept;

        ~TransformChangeObserver() override final;

        TransformChangeObserver& operator=(TransformChangeObserver&&) noexcept;

        void update(const TransformObserverSubject&, const TransformObserverEventArg&) const override final;
      private:
        TransformChangeObserver(const TransformChangeObserver&) = delete;
        TransformChangeObserver& operator=(const TransformChangeObserver&) = delete;

        TransformNode* mNode;
      };

      /********************************/

      TransformNode(SceneGraph&, GameObjectPtr);
      ~TransformNode() override final;

      void accept(ISceneGraphVisitor&) override final;

      const K9Math::Transform getTransform() const;

    private:
      TransformNode(const TransformNode&) = delete;
      TransformNode(TransformNode&& other) noexcept = delete;
      TransformNode& operator=(const TransformNode&) = delete;
      TransformNode& operator=(TransformNode&&) noexcept = delete;
      std::shared_ptr<TransformChangeObserver> mTransformChangeObserver;
      GameObjectPtr mGameObject;

    };
  }
}