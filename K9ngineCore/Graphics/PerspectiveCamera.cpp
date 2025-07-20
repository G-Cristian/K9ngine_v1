#include "PerspectiveCamera.h"

#include "Camera.h"
#include "../Math/Math.h"
#include "../Math/Transform.h"

namespace K9ngineCore {
  namespace K9Graphics {

    PerspectiveCamera::PerspectiveCamera(float aspect)
      : PerspectiveCamera(aspect, 1.0472f, 0.1f, 1000.0f)
    {
    }

    PerspectiveCamera::PerspectiveCamera(float aspect, float fovy, float zNear, float zFar)
      : Camera{}
      , mPerspectiveMatrix{K9Math::perspective(fovy, aspect, zNear, zFar)}
    {
    }

    void PerspectiveCamera::moveTo(const K9Math::Vec4& location)
    {
      mTransform.setLocation(-location);
    }

    void PerspectiveCamera::move(const K9Math::Vec3& delta)
    {
      mTransform.translate(-delta);
    }

    const K9Math::Vec4& PerspectiveCamera::getLocation() const
    {
      return -mTransform.getLocation();
    }

    void PerspectiveCamera::setRotation(const K9Math::Vec3& rotation)
    {
      mTransform.setRotation(-rotation);
    }

    const K9Math::Vec3& PerspectiveCamera::getRotation() const
    {
      return -mTransform.getRotation();
    }

    const K9Math::Mat4& PerspectiveCamera::getViewMatrix()
    {
      return mTransform.getTransformMat4();
    }

    const K9Math::Mat4& PerspectiveCamera::getViewMatrix() const
    {
      return mTransform.getTransformMat4();
    }

    const K9Math::Mat4& PerspectiveCamera::getProjectionMatrix() const
    {
      return mPerspectiveMatrix;
    }
  }
}