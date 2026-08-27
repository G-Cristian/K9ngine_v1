#pragma once

#include "../Common/Hasher.h"
#include "GraphicsContext.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class Texture
    {
    public:
      using Hash = Common::Hash;

      Texture(const Hash& id, K9uint textureId);
      ~Texture() = default;

      Texture(Texture&&) noexcept = default;
      Texture& operator=(Texture&&) noexcept = default;

      const Hash& getId() const;
      K9uint getTextureId() const;
    private:
      Texture(const Texture&) = delete;
      Texture& operator=(const Texture&) = delete;
      Hash mId{};
      K9uint mTextureId{};
    };
  }
}
