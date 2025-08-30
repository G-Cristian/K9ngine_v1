#pragma once

#include "GraphicsContext.h"
#include "MaterialProperty.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class ShaderProgram;

    class FloatMaterialProperty : public MaterialProperty {
    public:
      explicit FloatMaterialProperty(const PropertyIdType&);
      FloatMaterialProperty(const PropertyIdType&, float);

      ~FloatMaterialProperty() override final = default;

      void useProperty(std::shared_ptr<ShaderProgram>) const override final;
      void setMat4(const K9Math::Mat4&) override final;
      void setString(std::string_view) override final;
      void setFloat(float) override final;
      void setInt(int) override final;
      void setBool(bool) override final;

    private:
      K9Math::Mat4 getMat4() const override final;
      std::string getString() const override final;
      float getFloat() const override final;
      int getInt() const override final;
      bool getBool() const override final;

      float mValue{ 0.0f };
    };
  }
}