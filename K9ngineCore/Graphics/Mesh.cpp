#include "Mesh.h"

#include <initializer_list>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    Mesh::Mesh(const std::vector<float>& flattenedCoordinates, unsigned int vertexSize, bool CCW)
      : mFlattenedCoordinates{ flattenedCoordinates }
      , mVertexSize{ vertexSize }
      , mCCW{ CCW }
    {
    }

    Mesh::Mesh(std::initializer_list<float> flattenedCoordinates, unsigned int vertexSize, bool CCW)
      : mFlattenedCoordinates{ flattenedCoordinates }
      , mVertexSize{ vertexSize }
      , mCCW{ CCW }
    {
    }

    const std::vector<float>& Mesh::getFlattenedCoordinates() const
    {
      return mFlattenedCoordinates;
    }

    unsigned int Mesh::getVertexSize() const
    {
      return mVertexSize;
    }

    size_t Mesh::getVertexCount() const
    {
      return mFlattenedCoordinates.size() / mVertexSize;
    }

    bool Mesh::isCCW() const
    {
      return mCCW;
    }
  }
}