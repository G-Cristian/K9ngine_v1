#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common/Hasher.h"
#include "Math/Math.h"

namespace K9ngineCore{
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  class GameObject {
  public:
    GameObject(Hash id);
    GameObject(Hash id, Vec4 location, Vec3 rotation, Vec3 scale);

    const Vec4& getLocation() const;
    void setLocation(Vec4);

    const Vec3& getRotation() const;
    void setRotation(Vec3);

    const Vec3& getScale() const;
    void setScale(Vec3);

    const Hash& getId() const;

  private:
    Vec4 mLocation;
    Vec3 mRotation;
    Vec3 mScale;
    Hash mId;
  };
}

#endif // !GAMEOBJECT_H
