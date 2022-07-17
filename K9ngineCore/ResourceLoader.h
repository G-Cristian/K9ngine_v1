#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "FileReader.h"
#include "Hasher.h"
#include "K9Debug.h"
#include "Path.h"
#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <fstream>
#include <memory>
#include <string>

namespace K9ngineCore {
	namespace IO {
		template<typename T>
		class ResourceLoader {
		public:
			static T* loadResource(const std::string& path);
		};

		template<typename T>
		T* ResourceLoader<T>::loadResource(const std::string& path) {
			// Not implemented for generic tempate
			K9ASSERT(false, "ResourceLoader<T>::loadResource not implemented for generic type");
			return nullptr;
		}

		/***** TEXTURE RESOURCE LOADER *****/

		template<>
		Graphics::TextureData* ResourceLoader<Graphics::TextureData>::loadResource(const std::string& path) {
			using namespace Graphics;
			std::string ext = Utility::Path::getExtension(path);
			if (ext == "tex") {
				int width = 0;
				int height = 0;
				int nrChannels = 0;
				int wrapModeS = 0;
				int wrapModeT = 0;
				int filterModeMin = 0;
				int filterModeMag = 0;
				bool gammaCorrect = false;
				bool flipY = false;
				unsigned char* data = nullptr;

				try {
					std::string infoPath = Utility::Path::getDirectory(path) +
						Utility::Path::Separator +
						Utility::Path::getFileNameWithoutExtension(path) +
						".info";

					FileReader fileReader(infoPath);
					

					K9ASSERT(fileReader.isOpen(), (std::string("Cannot open file ") + infoPath).c_str());
					if (fileReader.isOpen()) {
						fileReader >> width >> height >> nrChannels
							       >> wrapModeS >> wrapModeT
							       >> filterModeMin >> filterModeMag
							       >> gammaCorrect
							       >> flipY;
					}

					if (width <= 0 || height <= 0 || nrChannels <= 0) {
						return nullptr;
					}

					std::ifstream imgFile;
					imgFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
					imgFile.open(path);
					K9ASSERT(imgFile.is_open(), (std::string("Cannot open file ") + path).c_str());
					if (imgFile.is_open()) {
						int bytesWidth = width * nrChannels;
						int size = bytesWidth * height;
						data = new unsigned char[size];
						int i = 0;
						int x = 0, y = 0;
						if (flipY) {
							y = height - 1;
						}

						unsigned char b;
						while (i != size && (imgFile >> b)) {
							int pos = x + y * bytesWidth;
							data[pos] = b;
							x++;
							if (x >= bytesWidth) {
								x = 0;
								if (flipY) {
									y--;
								}
								else {
									y++;
								}
							}
							i++;
						}

						if (i != size) {
							data[x + y * bytesWidth] = b;
						}

						imgFile.close();
					}
				}
				catch (std::ifstream::failure e) {
					K9ASSERT(false, (std::string("Error loading texture data. ") + e.what()).c_str());
					return nullptr;
				}

				return new TextureData(width, height,
					nrChannels,
					(TextureWrapMode)wrapModeS, (TextureWrapMode)wrapModeT,
					(TextureFilterMode)filterModeMin, (TextureFilterMode)filterModeMag,
					gammaCorrect,
					flipY,
					data);
			}

			return nullptr;
		}

		template<>
		Graphics::Texture* ResourceLoader<Graphics::Texture>::loadResource(const std::string& path) {
			using namespace Graphics;
			//TODO: Use gamma correct as appropiate.
			std::unique_ptr<TextureData> data(ResourceLoader<TextureData>::loadResource(path));
			K9ASSERT(data, (std::string("Couldn't load texture ") + path).c_str());
			if (!data) {
				return nullptr;
			}

			GLuint textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, K9WrapModeToAPI(data->wrapModeS()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, K9WrapModeToAPI(data->wrapModeT()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, K9FilterModeToAPI(data->filterModeMin()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, K9FilterModeToAPI(data->filterModeMag()));

			K9ASSERT(data->data(), (std::string("Invalid texture data for image ") + path).c_str());
			if (!data->data()) {
				return nullptr;
			}

			GLint channelsFormat = K9NumberOfChannelsToAPI(data->numberOfChannels());
			glTexImage2D(GL_TEXTURE_2D, 0, channelsFormat, data->width(), data->height(), 0, channelsFormat, GL_UNSIGNED_BYTE, (const void*)data->data());
			glGenerateMipmap(GL_TEXTURE_2D);

			return new Texture(Utility::hashString(path), textureID);
		}
	}
}

#endif // !RESOURCELOADER_H
