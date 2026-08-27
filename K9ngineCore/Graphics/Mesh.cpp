#include "Mesh.h"

#include <initializer_list>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    Mesh::Mesh(const std::vector<float>& flattenedCoordinates, unsigned int vertexSize, bool CCW)
      : Mesh(flattenedCoordinates, std::vector<float>(), vertexSize, CCW)
    {
    }

    Mesh::Mesh(std::initializer_list<float> flattenedCoordinates, unsigned int vertexSize, bool CCW)
      : Mesh(flattenedCoordinates, {}, vertexSize, CCW)
    {
    }

    Mesh::Mesh(const std::vector<float>& flattenedCoordinates, const std::vector<float>& textureCoordinates, unsigned int vertexSize, bool CCW)
      : mFlattenedCoordinates{ flattenedCoordinates }
      , mTextureCoordinates{ textureCoordinates }
      , mVertexSize{ vertexSize }
      , mCCW{ CCW }
    {
    }

    Mesh::Mesh(std::initializer_list<float> flattenedCoordinates, std::initializer_list<float> textureCoordinates, unsigned int vertexSize, bool CCW)
      : mFlattenedCoordinates{ flattenedCoordinates }
      , mTextureCoordinates{ textureCoordinates }
      , mVertexSize{ vertexSize }
      , mCCW{ CCW }
    {
    }

    const std::vector<float>& Mesh::getFlattenedCoordinates() const
    {
      return mFlattenedCoordinates;
    }

    const std::vector<float>& Mesh::getTextureCoordinates() const
    {
      return mTextureCoordinates;
    }

    unsigned int Mesh::getVertexSize() const
    {
      return mVertexSize;
    }

    size_t Mesh::getVertexCount() const
    {
      return mFlattenedCoordinates.size() / mVertexSize;
    }

    size_t Mesh::getTextureCoordinatesCount() const
    {
      return mTextureCoordinates.size() / 2;
    }

    bool Mesh::isCCW() const
    {
      return mCCW;
    }
  }
}