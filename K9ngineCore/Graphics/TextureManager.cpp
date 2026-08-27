#include "TextureManager.h"

#include "../Common/Hasher.h"
#include "../Handle.h"
#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "Texture.h"

#include <format>
#include <SOIL2/SOIL2.h>
#include <string_view>
#include <unordered_map>

namespace K9ngineCore {
  namespace K9Graphics {
    ConstTexturePtr TextureManager::createIfNewTexture(std::string_view path)
    {
      Hash textureIdKey = Common::hashString(path);
      //K9ASSERT(!hasTextureId(textureIdKey), "TextureManager::createTexture, texture with path [%s] already exists", path.data());
      bool beenCreated = hasTextureId(textureIdKey);
      K9uint textureId = beenCreated
                          ? getTextureId(textureIdKey)
                          : SOIL_load_OGL_texture(path.data(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

      mTexturesIds[textureIdKey] = textureId;
      auto handleId = Common::hashToUInt64(textureIdKey);
      auto handle = mTextures.findHandle(handleId);

      return handle ? handle : mTextures.getHandle(mTextures.createHandle(handleId, textureIdKey, textureId));
    }

    //TexturePtr TextureManager::copyTexture(const Hash& id);
    //TexturePtr TextureManager::copyTexture(const Texture& texture);

    bool TextureManager::hasTextureId(const Hash& id) const {
      return mTexturesIds.contains(id);
    }

    bool TextureManager::hasTexture(const Hash& id) const {
      return hasTextureId(id) && mTextures.findHandle(Common::hashToUInt64(id));
    }
    ConstTexturePtr TextureManager::getTexture(const Hash& id) const {
      K9ASSERT(hasTexture(id), std::format("TextureManager::getTexture, texture with id {} doesn't exist", id).c_str());
      return hasTexture(id) ? mTextures.getHandle(Common::hashToUInt64(id)) : mTextures.ConstNullHandle;
    }

    K9uint TextureManager::getTextureId(const Hash& id) const {
      K9ASSERT(hasTextureId(id), std::format("TextureManager::getTextureId, texture with id {} doesn't exist", id).c_str());
      return hasTextureId(id) ? mTexturesIds.at(id) : 0;
    }
  }
}