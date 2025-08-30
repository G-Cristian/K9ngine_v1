#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "GraphicsContext.h"
#include "Mat4MaterialProperty.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"
#include "../Math/Math.h"


namespace K9ngineCore {
  namespace K9Graphics {
    struct VertexBufferObjectData;

    class Material {
      using PropertiesContainer = std::unordered_map<MaterialProperty::PropertyIdType, std::shared_ptr<MaterialProperty>>;
      using AttributesContainer = std::unordered_map<std::string, K9uint>;
    public:
      explicit Material(std::shared_ptr<ShaderProgram> program);

      Material(const Material&);
      //Material(Material&&) noexcept;

      Material& operator=(const Material&);
      //Material& operator=(Material&&) noexcept;

      void addOrSetProperty(std::shared_ptr<MaterialProperty>);
      bool hasProperty(const MaterialProperty::PropertyIdType&) const;
      std::shared_ptr<const MaterialProperty> getProperty(const MaterialProperty::PropertyIdType&) const;

      void useProperty(const MaterialProperty::PropertyIdType&) const;
      void useProperties() const;

      void addOrAssignAttributeLocation(std::string_view name, K9uint location);
      bool hasAttributeLocation(std::string_view name) const;
      K9uint getAttrLocation(std::string_view name) const;

      /*
      * Binds the buffer, sets the attribute pointer and enables the vertex attribute array
      * @param vbo The vertex buffer object
      * @param data Information to bind the buffer (target buffer) and data for the attribute pointer.
      */
      bool setVertexAttribute(K9uint vbo, const VertexBufferObjectData& data) const;

      void addModelMatrixProperty(const Mat4MaterialProperty&);
      K9Math::Mat4 getModelMatrix() const;
      bool setModelMatrix(const K9Math::Mat4&) const;
      bool checkAndSetModelMatrix(const K9Math::Mat4&) const;

      void addViewMatrixProperty(const Mat4MaterialProperty&);
      K9Math::Mat4 getViewMatrix() const;
      bool setViewMatrix(const K9Math::Mat4&) const;
      bool checkAndSetViewMatrix(const K9Math::Mat4&) const;

      void addModelViewMatrixProperty(const Mat4MaterialProperty&);
      K9Math::Mat4 getModelViewMatrix() const;
      bool setModelViewMatrix(const K9Math::Mat4&) const;
      bool checkAndSetModelViewMatrix(const K9Math::Mat4&) const;

      void addProjectionMatrixProperty(const Mat4MaterialProperty&);
      K9Math::Mat4 getProjectionMatrix() const;
      bool setProjectionMatrix(const K9Math::Mat4&) const;
      bool checkAndSetProjectionMatrix(const K9Math::Mat4&) const;

      bool use() const;
    private:
      PropertiesContainer mProperties{};
      AttributesContainer mAttributes{};

      std::unique_ptr<Mat4MaterialProperty> mModelMatrix{ nullptr };
      std::unique_ptr<Mat4MaterialProperty> mViewMatrix{ nullptr };
      std::unique_ptr<Mat4MaterialProperty> mModelViewMatrix{ nullptr };
      std::unique_ptr<Mat4MaterialProperty> mProjectionMatrix{ nullptr };

      std::shared_ptr<ShaderProgram> mProgram{nullptr};
    };
  }
}

#endif
