#pragma once

#include "../Math/Math.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class Camera {
    public:
      virtual ~Camera() = default;
      virtual const K9Math::Mat4& getViewMatrix() = 0;
      virtual const K9Math::Mat4& getViewMatrix() const = 0;
      virtual void setProjectionMatrix(const K9Math::Mat4&) = 0;
      virtual void setProjectionMatrix(K9Math::Mat4&&) = 0;
      virtual const K9Math::Mat4& getProjectionMatrix() const = 0;

      virtual void changeAspect(float) = 0;
      virtual float getAspect() const = 0;
      virtual float getNearClippingPlane() const = 0;
      virtual float getFarClippingPlane() const = 0;

      void moveTo(float x, float y, float z) { moveTo(K9Math::Vec4(x,y,z, 1.0)); }
      virtual void moveTo(const K9Math::Vec4& location) = 0;

      void move(float dx, float dy, float dz) { move(K9Math::Vec3(dx, dy, dz)); }
      virtual void move(const K9Math::Vec3& delta) = 0;

      virtual const K9Math::Vec4& getLocation() const = 0;

      void setRotation(float pitch, float yaw, float roll) { setRotation(K9Math::Vec3(pitch, yaw, roll)); }
      virtual void setRotation(const K9Math::Vec3& rotation) = 0;
      virtual const K9Math::Vec3& getRotation() const = 0;
    };
  }
}