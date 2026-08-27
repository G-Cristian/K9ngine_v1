#pragma once

#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class Mesh
    {
    public:
      explicit Mesh(const std::vector<float>& flattenedCoordinates, unsigned int vertexSize, bool CCW);
      explicit Mesh(std::initializer_list<float> flattenedCoordinates, unsigned int vertexSize, bool CCW);

      explicit Mesh(const std::vector<float>& flattenedCoordinates, const std::vector<float>& textureCoordinates, unsigned int vertexSize, bool CCW);
      explicit Mesh(std::initializer_list<float> flattenedCoordinates, std::initializer_list<float> textureCoordinates, unsigned int vertexSize, bool CCW);

      const std::vector<float>& getFlattenedCoordinates() const;
      const std::vector<float>& getTextureCoordinates() const;
      unsigned int getVertexSize() const;
      size_t getVertexCount() const;
      size_t getTextureCoordinatesCount() const;

      bool isCCW() const;
    private:
      std::vector<float> mFlattenedCoordinates;
      std::vector<float> mTextureCoordinates;
      unsigned int mVertexSize{};
      bool mCCW{ true };
    };
  }
}
