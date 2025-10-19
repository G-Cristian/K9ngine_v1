#include "K9Debug.h"

#include "GameObject.h"

#include "Common/Hasher.h"
#include "CommonHandleTypes.h"
#include "Math/Math.h"
#include "World.h"

namespace K9ngineCore {
  using namespace K9ngineCore::Common;
  using namespace K9ngineCore::K9Math;
  GameObject::GameObject(const Hash& id)
    : GameObject(id, Transform{}) {
  }

  GameObject::GameObject(const Hash& id, const Transform& transform)
    : mId{ id }
    , mAttachedGameObjects {}
    , mTransformChangeEvent{this}
    , mParentGameObject{}
    , mTransform{ transform }
  {
  }

  GameObject::GameObject(GameObject&& other) noexcept
    : mId{ std::move(other.mId) }
    , mAttachedGameObjects{ std::move(other.mAttachedGameObjects) }
    , mTransformChangeEvent{ this }
    , mParentGameObject{ std::move(other.mParentGameObject) }
    , mTransform{ std::move(other.mTransform) }
    , mCombineParentTranslation{ other.mCombineParentTranslation }
    , mCombineParentRotation{ other.mCombineParentRotation }
    , mCombineParentScale{ other.mCombineParentScale }
  {
    other.mTransformChangeEvent.moveObserversTo(mTransformChangeEvent);
  }

  void GameObject::addObserver(ObserverTypePtr observer) {
    mTransformChangeEvent += observer;
  }

  void GameObject::removeObserver(ObserverTypePtr observer) {
    mTransformChangeEvent -= observer;
  }

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

  GameObjectPtr GameObject::getParent() const { return mParentGameObject; }

  void GameObject::setCombineParentTranslation(bool combine) { mCombineParentTranslation = combine; }
  bool GameObject::getCombineParentTranslation() const { return mCombineParentTranslation; }
  void GameObject::setCombineParentRotation(bool combine) { mCombineParentRotation = combine; }
  bool GameObject::getCombineParentRotation() const { return mCombineParentRotation; }
  void GameObject::setCombineParentScale(bool combine) { mCombineParentScale = combine; }
  bool GameObject::getCombineParentScale() const { return mCombineParentScale; }

  K9Math::Transform GameObject::getWorldTransform() const
  {
    if (mParentGameObject) {
      const auto& parentTransform = mParentGameObject->getTransform();
      auto compensatingTransform = Transform::identity();
      if (!mCombineParentTranslation) {
        compensatingTransform = Transform::buildTranslate(-parentTransform.getLocation()) * compensatingTransform;
      }

      if (!mCombineParentRotation) {
        compensatingTransform = Transform::buildInverseRotate(parentTransform.getRotation()) * compensatingTransform;
      }

      if (!mCombineParentScale) {
        compensatingTransform = Transform::buildScale(K9Math::Vec3{ 1.0f } / parentTransform.getScale()) * compensatingTransform;
      }

      return compensatingTransform * mTransform;
    }
    else {
      return mTransform;
    }
  }

  const Transform& GameObject::getTransform() const { return mTransform; }

  void GameObject::attachGameObject(GameObjectPtr child)
  {
    mAttachedGameObjects.push_back(child);
  }

  void GameObject::setParentGameObject(GameObjectPtr gameObject)
  {
    mParentGameObject = gameObject;
  }
}