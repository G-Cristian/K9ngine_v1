#include "TextureProperty.h"

#include "../Common/Hasher.h"
#include "../Handle.h"
#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "MaterialProperty.h"
#include "Texture.h"

namespace K9ngineCore {
  namespace K9Graphics {
    TextureProperty::TextureProperty(const PropertyIdType& id, K9uint textureId, TargetTexture target, TextureSampler sampler)
      : MaterialProperty(id)
      , mTextureId(textureId)
      , mTarget(target)
      , mSampler(sampler) {
    }

    TextureProperty::TextureProperty(const PropertyIdType& id, ConstTexturePtr& texture, TargetTexture target, TextureSampler sampler)
      : TextureProperty(id, texture ? texture->getTextureId() : 0, target, sampler) {
      K9ASSERT(texture, std::format("TextureProperty::TextureProperty, texture is null for property id {}", id).c_str());
    }

    void TextureProperty::useProperty(std::shared_ptr<ShaderProgram>) const {
      GraphicsContext::setActiveTexture(mSampler);
      GraphicsContext::bindTexture(mTarget, mTextureId);
    }

    void TextureProperty::setMat4(const K9Math::Mat4&) {
      K9ASSERT(false, "TextureProperty::setMat4() not supported.");
    }

    void TextureProperty::setString(std::string_view) {
      K9ASSERT(false, "TextureProperty::setString() not supported.");
    }
    void TextureProperty::setFloat(float) {
      K9ASSERT(false, "TextureProperty::setFloat() not supported.");
    }
    void TextureProperty::setInt(int) {
      K9ASSERT(false, "TextureProperty::setInt() not supported.");
    }
    void TextureProperty::setBool(bool){
      K9ASSERT(false, "TextureProperty::setBool() not supported.");
    }

    K9Math::Mat4 TextureProperty::getMat4() const {
      K9ASSERT(false, "TextureProperty::getMat4() not supported.");
      return K9Math::identityMat4();
    }

    std::string TextureProperty::getString() const {
      K9ASSERT(false, "TextureProperty::getString() not supported.");
      return std::string();
    }

    float TextureProperty::getFloat() const {
      K9ASSERT(false, "TextureProperty::getFloat() not supported.");
      return 0.0f;
    }

    int TextureProperty::getInt() const {
      K9ASSERT(false, "TextureProperty::getInt() not supported.");
      return 0;
    }

    bool TextureProperty::getBool() const {
      K9ASSERT(false, "TextureProperty::getBool() not supported.");
      return false;
    }
  }
}