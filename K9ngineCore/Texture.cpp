#include "Texture.h"

#include "K9Debug.h"

#include <glad/glad.h>

namespace K9ngineCore {
	namespace Graphics {
		GLint K9WrapModeToAPI(TextureWrapMode wrapMode) {
			if (wrapMode == TextureWrapMode::REPEAT) {
				return GL_REPEAT;
			}
			if (wrapMode == TextureWrapMode::CLAMP_TO_EDGE) {
				return GL_CLAMP_TO_EDGE;
			}

			K9ASSERT(false, "Invalid TextureWrapMode");
			return GL_CLAMP_TO_EDGE;
		}

		GLint K9FilterModeToAPI(TextureFilterMode filterMode) {
			if (filterMode == TextureFilterMode::LINEAR) {
				return GL_LINEAR;
			}

			if (filterMode == TextureFilterMode::LINEAR_MIPMAP_LINEAR) {
				return GL_LINEAR_MIPMAP_LINEAR;
			}

			if (filterMode == TextureFilterMode::NEAREST) {
				return GL_NEAREST;
			}

			K9ASSERT(false, "Invalid TextureFilterMode");
			return GL_NEAREST;
		}

		GLint K9NumberOfChannelsToAPI(int numberOfChannels) {
			if (numberOfChannels == 3) {
				return GL_RGB;
			}
			if (numberOfChannels == 4) {
				return GL_RGBA;
			}

			K9ASSERT(false, "Invalid number of channels");
			return GL_RGB;
		}

		Texture& Texture::operator=(Texture&& rhs) noexcept {
			if (&rhs != this) {
				_guid = rhs._guid;
				_texId = rhs._texId;

				rhs._guid = 0;
				rhs._texId = 0;
			}

			return *this;
		}

		TextureData& TextureData::operator=(TextureData&& rhs) noexcept {
			if (&rhs != this) {
				_width = rhs._width;
				_height = rhs._height;
				_numberOfChannels = rhs._numberOfChannels;
				_wrapModeS = rhs._wrapModeS;
				_wrapModeT = rhs._wrapModeT;
				_filterModeMin = rhs._filterModeMin;
				_filterModeMag = rhs._filterModeMag;
				_gammaCorrect = rhs._gammaCorrect;
				_flipY = rhs._flipY;
				_data = rhs._data;

				rhs._data = nullptr;
			}

			return *this;
		}
	}
}