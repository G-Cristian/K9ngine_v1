#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <cstdint>

namespace K9ngineCore {
	namespace Graphics {
		//TODO: remove if not needed.
		//enum class TextureFormat { RGB24, ARGB32 };
		enum class TextureWrapMode { REPEAT, CLAMP_TO_EDGE };
		enum class TextureFilterMode { NEAREST, LINEAR, LINEAR_MIPMAP_LINEAR };

		GLint K9WrapModeToAPI(TextureWrapMode wrapMode);
		GLint K9FilterModeToAPI(TextureFilterMode filterMode);
		GLint K9NumberOfChannelsToAPI(int numberOfChannels);

		class Texture {
		public:
			Texture(uint64_t guid, GLuint texId) :
				_guid(guid),
				_texId(texId) {
			}
			Texture(const Texture& rhs) :
				_guid(rhs._guid),
				_texId(rhs._texId) {
			}
			Texture(Texture&& rhs) noexcept :
				_guid(rhs._guid),
				_texId(rhs._texId) {
				rhs._guid = 0;
				rhs._texId = 0;
			}
			
			Texture& operator=(const Texture& rhs) {
				_guid = rhs._guid;
				_texId = rhs._texId;
				return *this;
			}

			Texture& operator=(Texture&& rhs) noexcept;

			uint64_t guid() const { return _guid; }
			GLuint texId() const { return _texId; }
		private:
			uint64_t _guid;
			GLuint _texId;
		};

		class TextureData {
		public:
			TextureData(int width, int height, int numberOfChannels, TextureWrapMode wrapModeS, TextureWrapMode wrapModeT, TextureFilterMode filterModeMin, TextureFilterMode filterModeMag, bool gammaCorrect, bool flipY, unsigned char* data) :
				_width(width),
				_height(height),
				_numberOfChannels(numberOfChannels),
				_wrapModeS(wrapModeS),
				_wrapModeT(wrapModeT),
				_filterModeMin(filterModeMin),
				_filterModeMag(filterModeMag),
				_gammaCorrect(gammaCorrect),
				_flipY(flipY),
				_data(data){
			}

			~TextureData() {
				if (_data) {
					delete[] _data;
				}
			}

			TextureData(const TextureData&) = delete;
			TextureData(TextureData&& rhs) noexcept :
				_width(rhs._width),
				_height(rhs._height),
				_numberOfChannels(rhs._numberOfChannels),
				_wrapModeS(rhs._wrapModeS),
				_wrapModeT(rhs._wrapModeT),
				_filterModeMin(rhs._filterModeMin),
				_filterModeMag(rhs._filterModeMag),
				_gammaCorrect(rhs._gammaCorrect),
				_flipY(rhs._flipY),
				_data(rhs._data)
			{
				rhs._data = nullptr;
			}

			TextureData& operator=(const TextureData&) = delete;
			TextureData& operator=(TextureData&& rhs) noexcept;

			int width() const { return _width; }
			int height() const { return _height; }
			int  numberOfChannels() const { return _numberOfChannels; }
			TextureWrapMode wrapModeS() const { return _wrapModeS; }
			TextureWrapMode wrapModeT() const { return _wrapModeT; }
			TextureFilterMode filterModeMin() const { return _filterModeMin; }
			TextureFilterMode filterModeMag() const { return _filterModeMag; }
			bool gammaCorrect() const { return _gammaCorrect; }
			bool flipY() const { return _flipY; }
			const unsigned char* data() const { return _data; }
		private:
			int _width;
			int _height;
			int _numberOfChannels;
			TextureWrapMode _wrapModeS;
			TextureWrapMode _wrapModeT;
			TextureFilterMode _filterModeMin;
			TextureFilterMode _filterModeMag;
			unsigned char* _data;
			bool _gammaCorrect;
			bool _flipY;
		};
	}
}

#endif // !TEXTURE_H
