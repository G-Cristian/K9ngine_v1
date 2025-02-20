#include "GameObject.h"

#include "Common/Hasher.h"
#include "Math/Math.h"

namespace K9ngineCore {
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  GameObject::GameObject(Hash id)
    : GameObject(id, Vec4{ 0.0, 0.0, 0.0, 1.0 }, Vec3{ 0.0, 0.0, 0.0 }, Vec3{ 1.0, 1.0, 1.0 }) {
  }

  GameObject::GameObject(Hash id, Vec4 location, Vec3 rotation, Vec3 scale)
    : mLocation{ location }
    , mRotation{ rotation }
    , mScale{ scale }
    , mId{ id } {
  }

  const Vec4& GameObject::getLocation() const { return mLocation; }
  void GameObject::setLocation(Vec4 location) { mLocation = location; }

  const Vec3& GameObject::getRotation() const { return mRotation; }
  void GameObject::setRotation(Vec3 rotation) { mRotation = rotation; }

  const Vec3& GameObject::getScale() const { return mScale; }
  void GameObject::setScale(Vec3 scale) { mScale = scale; }

  const Hash& GameObject::getId() const { return mId; }
}