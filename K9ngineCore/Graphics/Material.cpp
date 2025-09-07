#include <format>
#include <memory>
#include <optional>
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
      :mProgram{ program != nullptr ? std::make_shared<ShaderProgram>(*program) : nullptr }
    {
      K9ASSERT(program != nullptr, "Shader program is null.");
      K9ASSERT(program != nullptr && program->isCorrect(), "Shader program incorrect.");
    }

    Material::Material(const Material& other)
      : mAttributes{other.mAttributes}
      , mProgram{ other.mProgram != nullptr ? std::make_shared<ShaderProgram>(*other.mProgram) : nullptr }
    {
      for (const auto& prop : other.mProperties) {
        addOrSetProperty(prop.second);
      }

      mModelMatrix = other.mModelMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mModelMatrix) : nullptr;
      mViewMatrix = other.mViewMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mViewMatrix) : nullptr;
      mModelViewMatrix = other.mModelViewMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mModelViewMatrix) : nullptr;
      mProjectionMatrix = other.mProjectionMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mProjectionMatrix) : nullptr;
    }

    Material::Material(Material&& other) noexcept
      : mAttributes{ std::move(other.mAttributes) }
      , mProperties{ std::move(other.mProperties) }
      , mModelMatrix{ std::move(other.mModelMatrix) }
      , mViewMatrix{ std::move(other.mViewMatrix) }
      , mModelViewMatrix{ std::move(other.mModelViewMatrix) }
      , mProjectionMatrix{ std::move(other.mProjectionMatrix) }
      , mProgram{ std::move(other.mProgram) }
    {
      other.mAttributes.clear();
      other.mProperties.clear();
      other.mModelMatrix = nullptr;
      other.mViewMatrix = nullptr;
      other.mModelViewMatrix = nullptr;
      other.mProjectionMatrix = nullptr;
      other.mProgram = nullptr;
    }

    Material& Material::operator=(const Material& other)
    {
      if (this != &other) {
        this->mAttributes = other.mAttributes;
        
        this->mProperties.clear();
        for (const auto& prop : other.mProperties) {
          this->addOrSetProperty(prop.second);
        }

        mModelMatrix = other.mModelMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mModelMatrix) : nullptr;
        mViewMatrix = other.mViewMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mViewMatrix) : nullptr;
        mModelViewMatrix = other.mModelViewMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mModelViewMatrix) : nullptr;
        mProjectionMatrix = other.mProjectionMatrix != nullptr ? std::make_unique<Mat4MaterialProperty>(*other.mProjectionMatrix) : nullptr;

        mProgram = other.mProgram != nullptr ? std::make_shared<ShaderProgram>(*other.mProgram) : nullptr;
      }

      return *this;
    }

    Material& Material::operator=(Material&& other) noexcept
    {
      if (this != &other) {
        this->mAttributes = std::move(other.mAttributes);
        this->mProperties = std::move(other.mProperties);
        this->mModelMatrix = std::move(other.mModelMatrix);
        this->mViewMatrix = std::move(other.mViewMatrix);
        this->mModelViewMatrix = std::move(other.mModelViewMatrix);
        this->mProjectionMatrix = std::move(other.mProjectionMatrix);
        this->mProgram = std::move(other.mProgram);

        other.mAttributes.clear();
        other.mProperties.clear();
        other.mModelMatrix = nullptr;
        other.mViewMatrix = nullptr;
        other.mModelViewMatrix = nullptr;
        other.mProjectionMatrix = nullptr;
        other.mProgram = nullptr;
      }

      return *this;
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

    void Material::addModelMatrixProperty(const Mat4MaterialProperty& matProp)
    {
      mModelMatrix = std::make_unique<Mat4MaterialProperty>(matProp);
    }

    K9Math::Mat4 Material::getModelMatrix() const
    {
      return mModelMatrix ? mModelMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setModelMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(!!mModelMatrix, "Model matrix property is not set.");
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

    void Material::addViewMatrixProperty(const Mat4MaterialProperty& matProp)
    {
      mViewMatrix = std::make_unique<Mat4MaterialProperty>(matProp);
    }

    K9Math::Mat4 Material::getViewMatrix() const
    {
      return mViewMatrix ? mViewMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setViewMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(!!mViewMatrix, "View matrix property is not set.");
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

    void Material::addModelViewMatrixProperty(const Mat4MaterialProperty& matProp)
    {
      mModelViewMatrix = std::make_unique<Mat4MaterialProperty>(matProp);
    }

    K9Math::Mat4 Material::getModelViewMatrix() const
    {
      return mModelViewMatrix ? mModelViewMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setModelViewMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(!!mModelViewMatrix, "Model view matrix property is not set.");
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

    void Material::addProjectionMatrixProperty(const Mat4MaterialProperty& matProp)
    {
      mProjectionMatrix = std::make_unique<Mat4MaterialProperty>(matProp);
    }

    K9Math::Mat4 Material::getProjectionMatrix() const
    {
      return mProjectionMatrix ? mProjectionMatrix->getValue<K9Math::Mat4>() : K9Math::identityMat4();
    }

    bool Material::setProjectionMatrix(const K9Math::Mat4& mat) const
    {
      K9ASSERT(!!mProjectionMatrix, "Projection matrix property is not set.");
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