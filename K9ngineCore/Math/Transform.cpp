#include "Transform.h"

#include "Math.h"
#include "../K9Debug.h"

namespace K9ngineCore {
  namespace K9Math {
    Transform::Transform()
    :Transform(Vec4{ 0.0, 0.0, 0.0, 1.0 }, Vec3{ 0.0, 0.0, 0.0 }, Vec3{ 1.0, 1.0, 1.0 }){
    }

    Transform::Transform(const Vec4& location, const Vec3& rotation, const Vec3& scale)
      : mTransformCache{1.0f}
      , mLocation{location}
      , mRotation{rotation}
      , mScale{scale}
    {
      buildTransformCache();
      mIsDirty = false;
    }

    Transform Transform::identity()
    {
      return Transform{};
    }

    const Mat4& Transform::getTransformMat4() const
    {
      /*K9ASSERT(!mIsDirty, "Since the transform object is const, it should not happend that it's dirty.");
      return mTransformCache;*/
      if (mIsDirty) {
        buildTransformCache();
        mIsDirty = false;
      }

      return mTransformCache;
    }

    const Vec4& Transform::getLocation() const { return mLocation; }

    void Transform::setLocation(const Vec4& location)
    {
      translate(location - mLocation);
    }

    void Transform::translate(const Vec3& delta)
    {
      mLocation += Vec4(delta, 0.0);
      mIsDirty = true;
    }

    const Vec3& Transform::getRotation() const { return mRotation; }

    void Transform::setRotation(const Vec3& rotation)
    {
      rotate(rotation - mRotation);
    }

    void Transform::rotate(const Vec3& delta)
    {
      mRotation += delta;
      mIsDirty = true;
    }

    const Vec3& Transform::getScale() const { return mScale; }

    void Transform::setScale(const Vec3& scale)
    {
      this->scale(scale / mScale);
    }

    void Transform::scale(const Vec3& delta)
    {
      mScale *= delta;
      mIsDirty = true;
    }

    void Transform::buildTransformCache() const
    {
      mTransformCache = K9Math::translate(rotateZ(rotateY(rotateX(K9Math::scale(K9Math::identityMat4(), mScale), mRotation.x), mRotation.y), mRotation.z), mLocation);
    }
  }
}