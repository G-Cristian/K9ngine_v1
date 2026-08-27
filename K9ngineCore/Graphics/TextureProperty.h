#pragma once

#include "../Common/Hasher.h"
#include "../Handle.h"
#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "MaterialProperty.h"
#include "Texture.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class ShaderProgram;

    class TextureProperty : public MaterialProperty {
    public:
      explicit TextureProperty(const PropertyIdType& id, K9uint textureId, TargetTexture target, TextureSampler sampler);
      TextureProperty(const PropertyIdType&, ConstTexturePtr& texture, TargetTexture target, TextureSampler sampler);
      ~TextureProperty() override final = default;
      void useProperty(std::shared_ptr<ShaderProgram>) const override final;
      void setMat4(const K9Math::Mat4&) override final;
      void setString(std::string_view) override final;
      void setFloat(float) override final;
      void setInt(int) override final;
      void setBool(bool) override final;

      void setTextureId(K9uint textureId) { mTextureId = textureId; }
      void setTargetTexture(TargetTexture target) { mTarget = target; }
      void setTextureSampler(TextureSampler sampler) { mSampler = sampler; }
    private:
      K9Math::Mat4 getMat4() const override final;
      std::string getString() const override final;
      float getFloat() const override final;
      int getInt() const override final;
      bool getBool() const override final;

      K9uint mTextureId{0};
      TargetTexture mTarget{ TargetTexture::K9_TEXTURE_2D };
      TextureSampler mSampler{ TextureSampler::K9_TEXTURE0 };
    };
  }
}