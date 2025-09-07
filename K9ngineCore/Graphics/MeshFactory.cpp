#include <vector>

#include "MeshFactory.h"

#include "Mesh.h"

namespace K9ngineCore {
  namespace K9Graphics {
    Mesh MeshFactory::createCube(float size /* = 1.0f */)
    {
      float halfSize = size * 0.5f;
      
      return Mesh{ std::vector<float>{
        -halfSize,  halfSize, -halfSize, -halfSize, -halfSize, -halfSize,  halfSize, -halfSize, -halfSize,
         halfSize, -halfSize, -halfSize, -halfSize,  halfSize, -halfSize, -halfSize,  halfSize, -halfSize,
         halfSize, -halfSize, -halfSize,  halfSize, -halfSize,  halfSize,  halfSize,  halfSize, -halfSize,
         halfSize, -halfSize,  halfSize,  halfSize,  halfSize,  halfSize,  halfSize,  halfSize, -halfSize,
         halfSize, -halfSize,  halfSize, -halfSize, -halfSize,  halfSize,  halfSize,  halfSize,  halfSize,
        -halfSize, -halfSize,  halfSize, -halfSize,  halfSize,  halfSize,  halfSize,  halfSize,  halfSize,
        -halfSize, -halfSize,  halfSize, -halfSize, -halfSize, -halfSize, -halfSize,  halfSize,  halfSize,
        -halfSize, -halfSize, -halfSize, -halfSize,  halfSize, -halfSize, -halfSize,  halfSize,  halfSize,
        -halfSize, -halfSize,  halfSize,  halfSize, -halfSize,  halfSize,  halfSize, -halfSize, -halfSize,
         halfSize, -halfSize, -halfSize, -halfSize, -halfSize, -halfSize, -halfSize, -halfSize,  halfSize,
        -halfSize,  halfSize, -halfSize,  halfSize,  halfSize, -halfSize,  halfSize,  halfSize,  halfSize,
         halfSize,  halfSize,  halfSize, -halfSize,  halfSize,  halfSize, -halfSize,  halfSize, -halfSize,
      }
      , 3 };
    }

    Mesh MeshFactory::createPyramid(float width /*= 1.0f*/, float depth /*= 1.0f*/, float height /*= 1.0f*/)
    {
      float halfWidth = width * 0.5f;
      float halfDepth = depth * 0.5f;
      float halfHeight = height * 0.5f;

      return Mesh(
        {
          -halfWidth, -halfHeight, halfDepth, halfWidth, -halfHeight, halfDepth, 0.0f, halfHeight, 0.0f,
           halfWidth, -halfHeight, halfDepth, halfWidth, -halfHeight, -halfDepth, 0.0f, halfHeight, 0.0f,
           halfWidth, -halfHeight, -halfDepth, -halfWidth, -halfHeight, -halfDepth, 0.0f, halfHeight, 0.0f,
           -halfWidth, -halfHeight, -halfDepth, -halfWidth, -halfHeight, halfDepth, 0.0f, halfHeight, 0.0f,
           -halfWidth, -halfHeight, -halfDepth, halfWidth, -halfHeight, halfDepth, -halfWidth, -halfHeight, halfDepth,
            halfWidth, -halfHeight, halfDepth, -halfWidth, -halfHeight, -halfDepth, halfWidth, -halfHeight, -halfDepth
        },
        3);
    }

    //static Mesh* createSphere(float radius = 1.0f, int segments = 16);
    //static Mesh* createPlane(float width = 1.0f, float height = 1.0f, int widthSegments = 1, int heightSegments = 1);
    //static Mesh* createCylinder(float radiusTop = 1.0f, float radiusBottom = 1.0f, float height = 1.0f, int radialSegments = 8, int heightSegments = 1);
    //static Mesh* createCone(float radius = 1.0f, float height = 1.0f, int radialSegments = 8);
    //static Mesh* createTorus(float radius = 1.0f, float tubeRadius = 0.2f, int radialSegments = 8, int tubularSegments = 16);
  }
}