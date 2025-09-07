#pragma once

#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class Mesh
    {
    public:
      explicit Mesh(const std::vector<float>& flattenedCoordinates, unsigned int vertexSize);
      explicit Mesh(std::initializer_list<float> flattenedCoordinates, unsigned int vertexSize);

      const std::vector<float>& getFlattenedCoordinates() const;
      unsigned int getVertexSize() const;
      size_t getVertexCount() const;
    private:
      std::vector<float> mFlattenedCoordinates;
      unsigned int mVertexSize{};
    };
  }
}
