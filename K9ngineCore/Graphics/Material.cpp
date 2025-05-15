#include "Material.h"

#include "GraphicsContext.h"
#include "K9Debug.h"
#include "VertexBufferObjectData.h"

#include <format>
#include <string>

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

    bool Material::setVertexAttribute(K9uint vbo, const VertexBufferObjectData& data) const
    {
      GraphicsContext::bindBuffer(data.targetBuffer, vbo);
      //auto attributeLocation = mMaterial.getAttrLocation(bufferObjectData.name);
      //GraphicsContext::setVertexAttributePointer(attributeLocation, bufferObjectData.size, bufferObjectData.type, bufferObjectData.isNormalized, bufferObjectData.stride, 0);
      //GraphicsContext::enableVertexAttribArray(attributeLocation);

      return true;
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