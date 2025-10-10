#pragma once

#include <format>

#include "Math.h"

namespace K9ngineCore {
  namespace K9Math {
    class Transform {
    private:
      friend Transform operator*(const Transform&, const Transform&);
    public:
      Transform();
      Transform(const Mat4&);
      Transform(const Vec4& location, const Vec3& rotation, const Vec3& scale);

      static Transform identity();
      static Transform buildTranslate(const Vec4& delta);
      static Transform buildRotateX(float angle);
      static Transform buildRotateY(float angle);
      static Transform buildRotateZ(float angle);
      static Transform buildRotate(const Vec3& angle);
      static Transform buildInverseRotate(const Vec3& angle);
      static Transform buildScale(const Vec3& value);

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

template<>
class std::formatter<K9ngineCore::K9Math::Transform>
{
public:
  constexpr auto parse(auto& ctx)
  {
    // TODO
    return end(ctx);
  }

  auto format(const K9ngineCore::K9Math::Transform& t, auto& ctx) const
  {
    return std::format_to(ctx.out(), "Transform(location={}, rotation={}, scale={})", std::format("{}", t.getLocation()), std::format("{}", t.getRotation()), std::format("{}", t.getScale()));
  }

};