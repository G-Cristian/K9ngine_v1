#ifndef MATH_H
#define MATH_H

#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/vec4.hpp"

namespace K9ngineCore {
  namespace K9Math {
    using Mat4 = glm::mat4;
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;

    Mat4 identityMat4();

    Mat4 translate(const Mat4& mat, const Vec3& delta);
    Mat4 rotateX(const Mat4& mat, float angle);
    Mat4 rotateY(const Mat4& mat, float angle);
    Mat4 rotateZ(const Mat4& mat, float angle);
    Mat4 scale(const Mat4& mat, const Vec3& value);

    Vec3 normalize(Vec3);
    Vec4 normalize(Vec4);
    float dot(Vec3, Vec3);
    float dot(Vec4, Vec4);
    Vec3 cross(Vec3, Vec3);
  }
}

#endif // !MATH_H
