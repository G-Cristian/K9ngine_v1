#ifndef MATERIAL_H
#define MATERIAL_H

#include "GraphicsContext.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"

#include <memory>
#include <string>
#include <unordered_map>


namespace K9ngineCore {
  namespace K9Graphics {
    struct VertexBufferObjectData;

    class Material {
      using PropertiesContainer = std::unordered_map<MaterialProperty::PropertyIdType, std::shared_ptr<MaterialProperty>>;
    public:
      explicit Material(std::shared_ptr<ShaderProgram> program);

      void addOrSetProperty(std::shared_ptr<MaterialProperty>);
      bool hasProperty(const MaterialProperty::PropertyIdType&) const;
      std::shared_ptr<const MaterialProperty> getProperty(const MaterialProperty::PropertyIdType&) const;

      /*
      * Binds the buffer, sets the attribute pointer and enables the vertex attribute array
      * @param vbo The vertex buffer object
      * @param data Information to bind the buffer (target buffer) and data for the attribute pointer.
      */
      bool setVertexAttribute(K9uint vbo, const VertexBufferObjectData& data) const;

      bool use() const;
    private:
      PropertiesContainer mProperties{};
      std::shared_ptr<ShaderProgram> mProgram;
    };
  }
}

#endif
