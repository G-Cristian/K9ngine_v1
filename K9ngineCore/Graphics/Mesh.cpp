#include "Mesh.h"

#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    Mesh::Mesh(const std::vector<float>& flattenedCoordinates, unsigned int vertexSize)
      : mFlattenedCoordinates{ flattenedCoordinates }
      , mVertexSize{ vertexSize }
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
  }
}