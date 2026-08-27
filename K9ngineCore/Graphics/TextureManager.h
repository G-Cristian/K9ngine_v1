#pragma once

#include "../Common/Hasher.h"
#include "../Handle.h"
#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "Texture.h"

#include <unordered_map>
#include <string_view>

namespace K9ngineCore {
  namespace K9Graphics {
    class TextureManager
    {
    public:
      using Hash = Texture::Hash;
      using TexturesIds = std::unordered_map<Hash, K9uint>;

      TextureManager() = default;
      ~TextureManager() = default;
      TextureManager(const TextureManager&) = delete;
      TextureManager& operator=(const TextureManager&) = delete;
      TextureManager(TextureManager&&) noexcept = delete;
      TextureManager& operator=(TextureManager&&) noexcept = delete;

      ConstTexturePtr createIfNewTexture(std::string_view);

      //TexturePtr copyTexture(const Hash& id);
      //TexturePtr copyTexture(const Texture& texture);
      
      bool hasTextureId(const Hash& id) const;
      K9uint getTextureId(const Hash& id) const;

      bool hasTexture(const Hash& id) const;
      ConstTexturePtr getTexture(const Hash& id) const;
    private:
      uint64_t mNextTextureUid{ 0 };
      TextureTable mTextures;
      TexturesIds mTexturesIds;
    };
  }
}