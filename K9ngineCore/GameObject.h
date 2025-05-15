#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common/Hasher.h"
#include "Common/IObserver.h"
#include "Common/TransformChangeEvent.h"
#include "Math/Math.h"
#include "Math/Transform.h"

#include <memory>

namespace K9ngineCore{
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  
  class GameObject {
  public:
    using TransformChangeEventType = TransformChangeEvent<GameObject>;
    using ObserverType = TransformChangeEventType::ObserverType;
    using ObserverTypePtr = TransformChangeEventType::ObserverTypePtr;

    GameObject(const Hash& id);
    GameObject(const Hash& id, const Transform& transform);

    void addObserver(ObserverTypePtr);
    void removeObserver(ObserverTypePtr);

    const Transform& getTransform() const;
    
    void moveTo(float x, float y, float z);
    void moveTo(const Vec3& location);

    void move(float x, float y, float z);
    void move(const Vec3& delta);

    void setScale(float x, float y, float z);
    void setScale(const Vec3& scale);

    void setRotation(float x, float y, float z);
    void setRotation(const Vec3& angle);

    const Hash& getId() const;

  private:
    TransformChangeEventType mTransformChangeEvent;
    Transform mTransform;
    Hash mId;
  };
}

#endif // !GAMEOBJECT_H
