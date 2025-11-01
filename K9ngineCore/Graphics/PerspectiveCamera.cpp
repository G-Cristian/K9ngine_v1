#include "../K9Debug.h"

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

    void PerspectiveCamera::setProjectionMatrix(const K9Math::Mat4& perspectiveMatrix)
    {
      mPerspectiveMatrix = perspectiveMatrix;
    }

    void PerspectiveCamera::setProjectionMatrix(K9Math::Mat4&& perspectiveMatrix)
    {
      mPerspectiveMatrix = std::move(perspectiveMatrix);
    }

    const K9Math::Mat4& PerspectiveCamera::getProjectionMatrix() const
    {
      return mPerspectiveMatrix;
    }

    void PerspectiveCamera::changeAspect(float aspect)
    {
      mPerspectiveMatrix = K9Math::perspective(getFOV_Y(), aspect, getNearClippingPlane(), getFarClippingPlane());
    }

    float PerspectiveCamera::getAspect() const
    {
      //m[0][0] = 1 / (aspect * tan(fovy/2))
      //m[1][1] = 1 / tan(fovy/2)
      //m[2][2] = -(zFar + zNear) / (zFar - zNear)
      //m[3][2] = -(2 * zFar * zNear) / (zFar - zNear)

      return mPerspectiveMatrix[1][1] / mPerspectiveMatrix[0][0];
    }

    float PerspectiveCamera::getNearClippingPlane() const
    {
      //m[0][0] = 1 / (aspect * tan(fovy/2))
      //m[1][1] = 1 / tan(fovy/2)
      //m[2][2] = -(zFar + zNear) / (zFar - zNear)
      //m[3][2] = -(2 * zFar * zNear) / (zFar - zNear)

      return mPerspectiveMatrix[3][2] / (mPerspectiveMatrix[2][2] - 1.0f);
    }

    float PerspectiveCamera::getFarClippingPlane() const
    {
      //m[0][0] = 1 / (aspect * tan(fovy/2))
      //m[1][1] = 1 / tan(fovy/2)
      //m[2][2] = -(zFar + zNear) / (zFar - zNear)
      //m[3][2] = -(2 * zFar * zNear) / (zFar - zNear)

      return mPerspectiveMatrix[3][2] / (mPerspectiveMatrix[2][2] + 1.0f);
    }

    float PerspectiveCamera::getFOV_Y() const
    {
      //m[0][0] = 1 / (aspect * tan(fovy/2))
      //m[1][1] = 1 / tan(fovy/2)
      //m[2][2] = -(zFar + zNear) / (zFar - zNear)
      //m[3][2] = -(2 * zFar * zNear) / (zFar - zNear)

      return 2.0f * atan(1.0f / mPerspectiveMatrix[1][1]);
    }
  }
}