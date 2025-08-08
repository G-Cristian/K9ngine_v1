#include <format>
#include <string>
#include <string_view>

#include "../K9Debug.h"

#include "Material.h"

#include "GraphicsContext.h"
#include "Mat4MaterialProperty.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"
#include "VertexBufferObjectData.h"
#include "../Math/Math.h"

namespace K9ngineCore {
  namespace K9Graphics {
    Material::Material(std::shared_ptr<ShaderProgram> program)
      :mProgram{program}
    {
      K9ASSERT(program != nullptr, "Shader program is null.");
      K9ASSERT(program != nullptr && program->isCorrect(), "Shader program incorrect.");
    }

    void Material::addOrSetProperty(std::shared_ptr<MaterialProperty> property) {
      mProperties[property->getId()] = property;
    }

    bool Material::hasProperty(const MaterialProperty::PropertyIdType& propertyId) const {
      return mProperties.contains(propertyId);
    }

    std::shared_ptr<const MaterialProperty> Material::getProperty(const MaterialProperty::PropertyIdType& propertyId) const {
      K9ASSERT(hasProperty(propertyId), std::format("Property {} not found.", propertyId).c_str());
      return hasProperty(propertyId) ? mProperties.at(propertyId) : nullptr;
    }

    void Material::useProperty(const MaterialProperty::PropertyIdType& propertyId) const
    {
      K9ASSERT(mProgram != nullptr, "Shader program is null.");
      if (mProgram) {
        auto property = getProperty(propertyId);
        if (property) {
          property->useProperty(mProgram);
        }
      }
    }

    void Material::useProperties() const
    {
      K9ASSERT(mProgram != nullptr, "Shader program is null.");
      if (mProgram) {
        if (mModelMatrix) {
          mModelMatrix->useProperty(mProgram);
        }
        if (mViewMatrix) {
          mViewMatrix->useProperty(mProgram);
        }
        if (mModelViewMatrix)
        {
          mModelViewMatrix->useProperty(mProgram);
        }
        if (mProjectionMatrix) {
          mProjectionMatrix->useProperty(mProgram);
        }

        for (const auto& property : mProperties) {
          if (property.second)
          {
            property.second->useProperty(mProgram);
          }
        }
      }
    }

    void Material::addOrAssignAttributeLocation(std::string_view name, K9uint location)
    {
      mAttributes[std::string{ name }] = location;
    }

    bool Material::hasAttributeLocation(std::string_view name) const
    {
      return mAttributes.contains(std::string{ name });
    }

    K9uint Material::getAttrLocation(std::string_view name) const
    {
      K9ASSERT(hasAttributeLocation(name), std::format("Attribute {} not found.", name).c_str());
      return hasAttributeLocation(name) ? mAttributes.at(std::string{ name }) : 0;
    }

    bool Material::setVertexAttribute(K9uint vbo, const VertexBufferObjectData& data) const
    {
      GraphicsContext::bindBuffer(data.targetBuffer, vbo);
      auto attributeLocation = getAttrLocation(data.name);
      GraphicsContext::setVertexAttributePointer(attributeLocation, data.size, data.type, data.isNormalized, data.stride, 0);
      GraphicsContext::enableVertexAttribArray(attributeLocation);

      return true;
    }

    void Material::addModelMatrixProperty(std::shared_ptr<Mat4MaterialProperty> matProp)
    {
      mModelMatrix = matProp;
    }

    K9Math::Mat4 Material::getModelMatrix() const
    {
      return mModelMatrix ? mModelMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setModelMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(mModelMatrix != nullptr, "Model matrix property is not set.");
      if (mModelMatrix) {
        mModelMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    bool Material::checkAndSetModelMatrix(const K9Math::Mat4& mat) const
    {
      if (mModelMatrix)
      {
        mModelMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    void Material::addViewMatrixProperty(std::shared_ptr<Mat4MaterialProperty> matProp)
    {
      mViewMatrix = matProp;
    }

    K9Math::Mat4 Material::getViewMatrix() const
    {
      return mViewMatrix ? mViewMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setViewMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(mViewMatrix != nullptr, "View matrix property is not set.");
      if (mViewMatrix) {
        mViewMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    bool Material::checkAndSetViewMatrix(const K9Math::Mat4& mat) const
    {
      if (mViewMatrix)
      {
        mViewMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    void Material::addModelViewMatrixProperty(std::shared_ptr<Mat4MaterialProperty> matProp)
    {
      mModelViewMatrix = matProp;
    }

    K9Math::Mat4 Material::getModelViewMatrix() const
    {
      return mModelViewMatrix ? mModelViewMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setModelViewMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(mModelViewMatrix != nullptr, "Model view matrix property is not set.");
      if (mModelViewMatrix) {
        mModelViewMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    bool Material::checkAndSetModelViewMatrix(const K9Math::Mat4& mat) const
    {
      if (mModelViewMatrix)
      {
        mModelViewMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    void Material::addProjectionMatrixProperty(std::shared_ptr<Mat4MaterialProperty> matProp)
    {
      mProjectionMatrix = matProp;
    }

    K9Math::Mat4 Material::getProjectionMatrix() const
    {
      return mProjectionMatrix ? mProjectionMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setProjectionMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(mProjectionMatrix != nullptr, "Projection matrix property is not set.");
      if (mProjectionMatrix) {
        mProjectionMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    bool Material::checkAndSetProjectionMatrix(const K9Math::Mat4& mat) const
    {
      if( mProjectionMatrix)
      {
        mProjectionMatrix->setMat4(mat);
        return true;
      }

      return false;
    }

    bool Material::use() const {
      K9ASSERT(mProgram != nullptr, "Shader program is null.");
      if (mProgram != nullptr) {
        mProgram->use();
        return true;
      }
      return false;
    }

  }
}