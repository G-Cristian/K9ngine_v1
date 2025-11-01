#pragma once

#include "Camera.h"
#include "../Math/Math.h"
#include "../Math/Transform.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class PerspectiveCamera: public Camera
    {
    public:
      using Camera::move;
      using Camera::moveTo;
      using Camera::setRotation;

      explicit PerspectiveCamera(float aspect);
      explicit PerspectiveCamera(float aspect, float fovy, float zNear, float zFar);

      ~PerspectiveCamera() override final = default;

      void moveTo(const K9Math::Vec4&) override final;
      void move(const K9Math::Vec3&) override final;
      const K9Math::Vec4& getLocation() const override final;

      void setRotation(const K9Math::Vec3&) override final;
      const K9Math::Vec3& getRotation() const override final;

      const K9Math::Mat4& getViewMatrix() override final;
      const K9Math::Mat4& getViewMatrix() const override final;
      void setProjectionMatrix(const K9Math::Mat4&) override final;
      void setProjectionMatrix(K9Math::Mat4&&) override final;
      const K9Math::Mat4& getProjectionMatrix() const override final;

      void changeAspect(float) override final;
      float getAspect() const override final;
      float getNearClippingPlane() const override final;
      float getFarClippingPlane() const override final;
      float getFOV_Y() const;

    private:
      K9Math::Transform mTransform;
      K9Math::Mat4 mPerspectiveMatrix;
    };
  }
}