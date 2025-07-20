#pragma once

#include "Math.h"

namespace K9ngineCore {
  namespace K9Math {
    class Transform {
    private:
      //friend Transform operator*(const Transform&, const Transform&);
    public:
      Transform();
      Transform(const Vec4& location, const Vec3& rotation, const Vec3& scale);

      static Transform identity();

      const Mat4& getTransformMat4() const;

      const Vec4& getLocation() const;
      void setLocation(const Vec4&);
      void translate(const Vec3&);


      const Vec3& getRotation() const;
      void setRotation(const Vec3&);
      void rotate(const Vec3&);

      const Vec3& getScale() const;
      void setScale(const Vec3&);
      void scale(const Vec3&);
    private:
      void buildTransformCache() const;

      mutable Mat4 mTransformCache;
      Vec4 mLocation;
      Vec3 mRotation;
      Vec3 mScale;
      mutable bool mIsDirty{ true };
    };
  }
}