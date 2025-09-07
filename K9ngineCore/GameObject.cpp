#include "K9Debug.h"

#include "GameObject.h"

#include "Common/Hasher.h"
#include "Math/Math.h"

namespace K9ngineCore {
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  GameObject::GameObject(const Hash& id)
    : GameObject(id, Transform{}) {
  }

  GameObject::GameObject(const Hash& id, const Transform& transform)
    : mTransformChangeEvent{this}
    , mTransform{ transform }
    , mId{ id } {
  }

  GameObject::GameObject(GameObject&& other) noexcept
    : mTransformChangeEvent{ this }
    , mTransform{ std::move(other.mTransform) }
    , mId{ std::move(other.mId) }
  {
    other.mTransformChangeEvent.moveObserversTo(mTransformChangeEvent);
  }

  void GameObject::addObserver(ObserverTypePtr observer) {
    mTransformChangeEvent += observer;
  }

  void GameObject::removeObserver(ObserverTypePtr observer) {
    mTransformChangeEvent -= observer;
  }

  const Transform& GameObject::getTransform() const { return mTransform; }

  void GameObject::moveTo(float x, float y, float z) {
    moveTo(Vec3(x, y, z));
  }

  void GameObject::moveTo(const Vec3& location) {
    const auto delta = location - Vec3(mTransform.getLocation());
    move(delta);
  }

  void GameObject::move(float x, float y, float z) {
    move(Vec3(x, y, z));
  }

  void GameObject::move(const Vec3& delta) {
    const auto oldTransform = mTransform;
    mTransform.translate(delta);
    mTransformChangeEvent.notify(oldTransform, mTransform);
  }

  void GameObject::setScale(float x, float y, float z) {
    setScale(Vec3(x, y, z));
  }

  void GameObject::setScale(const Vec3& scale) {
    const auto oldTransform = mTransform;
    mTransform.setScale(scale);
    mTransformChangeEvent.notify(oldTransform, mTransform);
  }

  void GameObject::setRotation(float x, float y, float z) {
    setRotation(Vec3(x, y, z));
  }

  void GameObject::setRotation(const Vec3& angle) {
    const auto oldTransform = mTransform;
    mTransform.setRotation(angle);
    mTransformChangeEvent.notify(oldTransform, mTransform);
  }

  const Hash& GameObject::getId() const { return mId; }
}