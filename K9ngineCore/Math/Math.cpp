#include "Math.h"

#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtx/matrix_decompose.hpp >
#include "glm/vec4.hpp"

namespace K9ngineCore {
  namespace K9Math {
    using Mat4 = glm::mat4;
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;

    const float* asValuePtr(const Mat4& mat)
    {
      return glm::value_ptr(mat);
    }

    Mat4 identityMat4()
    {
      return Mat4{1.0f};
    }

    Mat4 initMat4(float value)
    {
      return Mat4{ value };
    }

    Mat4 perspective(float fovy, float aspect, float zNear, float zFar)
    {
      return glm::perspective(fovy, aspect, zNear, zFar);
    }

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

    Mat4 rotate(const Mat4& mat, Vec3 angle)
    {
      return rotateZ(rotateX(rotateY(mat, angle.y), angle.x), angle.z);
    }

    Mat4 inverseRotate(const Mat4& mat, Vec3 angle)
    {
      return rotateY(rotateX(rotateZ(mat, -angle.z), -angle.x), -angle.y);
    }

    Mat4 scale(const Mat4& mat, const Vec3& value) {
      return glm::scale(mat, value);
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec3& outTranslation)
    {
      Vec3 skew;
      Vec4 perspective;
      
      return glm::decompose(modelMatrix, outScale, outOrientation, outTranslation, skew, perspective);
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec3& outTranslation, Vec3& outSkew, Vec4& outPerspective)
    {
      return glm::decompose(modelMatrix, outScale, outOrientation, outTranslation, outSkew, outPerspective);
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec4& outTranslation)
    {
      Vec3 skew;
      Vec4 perspective;

      return decompose(modelMatrix, outScale, outOrientation, outTranslation, skew, perspective);
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Quat& outOrientation, Vec4& outTranslation, Vec3& outSkew, Vec4& outPerspective)
    {
      Vec3 translation{ outTranslation.x, outTranslation.y, outTranslation.z };
      bool result = decompose(modelMatrix, outScale, outOrientation, translation, outSkew, outPerspective);
      outTranslation = Vec4{ translation.x, translation.y, translation.z, 1.0f };

      return result;
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Vec3& outOrientation, Vec4& outTranslation)
    {
      Vec3 skew;
      Vec4 perspective;

      return decompose(modelMatrix, outScale, outOrientation, outTranslation, skew, perspective);
    }

    bool decompose(const Mat4& modelMatrix, Vec3& outScale, Vec3& outOrientation, Vec4& outTranslation, Vec3& outSkew, Vec4& outPerspective)
    {
      Quat rotQuat;
      bool result = decompose(modelMatrix, outScale, rotQuat, outTranslation, outSkew, outPerspective);
      rotQuat = normalize(rotQuat);

      // Yaw (Y), Pitch (X), Roll (Z) in radians
      float yawY = yaw(rotQuat);    // rotation about +Y
      float pitchX = pitch(rotQuat);  // rotation about +X
      float rollZ = roll(rotQuat);   // rotation about +Z

      // Convert to degrees
      outOrientation = Vec3(pitchX, yawY, rollZ);

      return result;
    }

    float length(Vec3 vec)
    {
      return glm::length(vec);
    }

    float length(Vec4 vec)
    {
      return glm::length(vec);
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

    Quat normalize(Quat quat)
    {
      return glm::normalize(quat);
    }

    float yaw(Quat quat)
    {
      return glm::yaw(quat);
    }

    float pitch(Quat quat)
    {
      return glm::pitch(quat);
    }

    float roll(Quat quat)
    {
      return glm::roll(quat);
    }
  }
}