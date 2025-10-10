#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>

#include "Common/Hasher.h"
#include "Common/IObserver.h"
#include "Common/TransformChangeEvent.h"
#include "CommonHandleTypes.h"
#include "Handle.h"
#include "Math/Math.h"
#include "Math/Transform.h"

namespace K9ngineCore{
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  
  class GameObject {
    friend class World;
  public:
    using TransformChangeEventType = TransformChangeEvent<GameObject>;
    using ObserverType = TransformChangeEventType::ObserverType;
    using ObserverTypePtr = TransformChangeEventType::ObserverTypePtr;

    GameObject(const Hash& id);
    GameObject(const Hash& id, const Transform& transform);
    GameObject(GameObject&&) noexcept;

    ~GameObject() = default;

    void addObserver(ObserverTypePtr);
    void removeObserver(ObserverTypePtr);
    
    void moveTo(float x, float y, float z);
    void moveTo(const Vec3& location);

    void move(float x, float y, float z);
    void move(const Vec3& delta);

    void setScale(float x, float y, float z);
    void setScale(const Vec3& scale);

    void setRotation(float x, float y, float z);
    void setRotation(const Vec3& angle);

    const Hash& getId() const;

    GameObjectPtr getParent() const;

    void setCombineParentTranslation(bool combine);
    bool getCombineParentTranslation() const;
    void setCombineParentRotation(bool combine);
    bool getCombineParentRotation() const;
    void setCombineParentScale(bool combine);
    bool getCombineParentScale() const;

    K9Math::Transform getWorldTransform() const;

    const Transform& getTransform() const;
  private:
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject& operator=(GameObject&&) noexcept = delete;

    void attachGameObject(GameObjectPtr);
    void setParentGameObject(GameObjectPtr);

    Hash mId;
    std::vector<GameObjectPtr> mAttachedGameObjects;
    TransformChangeEventType mTransformChangeEvent;
    GameObjectPtr mParentGameObject;
    Transform mTransform;
    bool mCombineParentTranslation{ true };
    bool mCombineParentRotation{ true };
    bool mCombineParentScale{ false };
  };
}

#endif // !GAMEOBJECT_H
