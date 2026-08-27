#include "Texture.h"

#include "../Common/Hasher.h"
#include "GraphicsContext.h"

namespace K9ngineCore {
  namespace K9Graphics {
    Texture::Texture(const Hash& id, K9uint textureId)
      : mId(id)
      , mTextureId(textureId)
    {
    }

    const Texture::Hash& Texture::getId() const {
      return mId;
    }

    K9uint Texture::getTextureId() const {
      return mTextureId;
    }
  }
}