#include "Math.h"

#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/vec4.hpp"

namespace K9ngineCore {
  namespace K9Math {
    using Mat4 = glm::mat4;
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;

    Mat4 translate(const Mat4& mat, const Vec3& delta) {
      return glm::translate(mat, delta);
    }

    Mat4 rotateX(const Mat4& mat, float angle) {
      return glm::rotate(mat, angle, Vec3{ 1, 0, 0 });
    }

    Mat4 rotateY(const Mat4& mat, float angle) {
      return glm::rotate(mat, angle, Vec3{ 0, 1, 0 });
    }

    Mat4 rotateZ(const Mat4& mat, float angle) {
      return glm::rotate(mat, angle, Vec3{ 0, 0, 1 });
    }

    Mat4 scale(const Mat4& mat, const Vec3& value) {
      return glm::scale(mat, value);
    }

    Vec3 normalize(Vec3 vec) {
      return glm::normalize(vec);
    }

    Vec4 normalize(Vec4 vec) {
      return glm::normalize(vec);
    }

    float dot(Vec3 vec1, Vec3 vec2) {
      return glm::dot(vec1, vec2);
    }

    float dot(Vec4 vec1, Vec4 vec2) {
      return glm::dot(vec1, vec2);
    }

    Vec3 cross(Vec3 vec1, Vec3 vec2) {
      return glm::cross(vec1, vec2);
    }
  }
}