#ifndef MATH_H
#define MATH_H

#include <format>

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec4.hpp"

namespace K9ngineCore {
  namespace K9Math {
    using Quat = glm::quat;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;

    const float* asValuePtr(const Mat4& mat);

    Mat4 identityMat4();
    Mat4 initMat4(float value);

    Mat4 perspective(float fovy, float aspect, float zNear, float zFar);

    Mat4 translate(const Mat4& mat, const Vec3& delta);
    Mat4 rotateX(const Mat4& mat, float angle);
    Mat4 rotateY(const Mat4& mat, float angle);
    Mat4 rotateZ(const Mat4& mat, float angle);
    Mat4 rotate(const Mat4& mat, Vec3 angle);
    Mat4 inverseRotate(const Mat4& mat, Vec3 angle);
    Mat4 scale(const Mat4& mat, const Vec3& value);

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec3& outTranslation);
    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec3& outTranslation, Vec3& outSkew, Vec4& outPerspective);
    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec4& outTranslation);
    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec4& outTranslation, Vec3& outSkew, Vec4& outPerspective);
    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Vec3& outOrientation, Vec4& outTranslation);
    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Vec3& outOrientation, Vec4& outTranslation, Vec3& outSkew, Vec4& outPerspective);

    float length(Vec3);
    float length(Vec4);
    Vec3 normalize(Vec3);
    Vec4 normalize(Vec4);
    float dot(Vec3, Vec3);
    float dot(Vec4, Vec4);
    Vec3 cross(Vec3, Vec3);

    Quat normalize(Quat);
    float yaw(Quat);
    float pitch(Quat);
    float roll(Quat);
  }
}

template<>
class std::formatter<K9ngineCore::K9Math::Vec4>
{
public:
  constexpr auto parse(auto& ctx)
  {
    // TODO
    return end(ctx);
  }
  auto format(const K9ngineCore::K9Math::Vec4& vec, auto& ctx) const
  {
    return std::format_to(ctx.out(), "Vec4({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
  }
};

template<>
class std::formatter<K9ngineCore::K9Math::Vec3>
{
  public:
  constexpr auto parse(auto& ctx)
  {
    // TODO
    return end(ctx);
  }
  auto format(const K9ngineCore::K9Math::Vec3& vec, auto& ctx) const
  {
    return std::format_to(ctx.out(), "Vec3({}, {}, {})", vec.x, vec.y, vec.z);
  }
};

#endif // !MATH_H
