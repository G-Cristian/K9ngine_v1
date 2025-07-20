#pragma once

#include "GraphicsContext.h"
#include "MaterialProperty.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class ShaderProgram;

    class Mat4MaterialProperty : public MaterialProperty {
    public:
      using Mat4Type = K9Math::Mat4;

      explicit Mat4MaterialProperty(const PropertyIdType&);
      Mat4MaterialProperty(const PropertyIdType&, const Mat4Type&);
      Mat4MaterialProperty(const PropertyIdType&, const Mat4Type&, K9sizei);
      Mat4MaterialProperty(const PropertyIdType&, const Mat4Type&, K9sizei, bool);

      ~Mat4MaterialProperty() override final = default;

      void useProperty(std::shared_ptr<ShaderProgram>) const override final;
      void setMat4(const Mat4Type&) override final;
      void setString(std::string_view) override final;
      void setFloat(float) override final;
      void setInt(int) override final;
      void setBool(bool) override final;

    private:
      Mat4Type getMat4() const override final;
      std::string getString() const override final;
      float getFloat() const override final;
      int getInt() const override final;
      bool getBool() const override final;

      Mat4Type mValue{ K9Math::identityMat4() };
      K9sizei mCount{ 1 };
      BoolValues mTranspose{ BoolValues::K9_FALSE };
    };
  }
}