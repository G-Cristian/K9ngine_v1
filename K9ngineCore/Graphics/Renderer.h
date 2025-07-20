#pragma once

#include "CommonHandleTypes.h"
#include "GraphicsHandleTypes.h"
#include "SceneGraph.h"

#include "../Common/Hasher.h"

#include <memory>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class BufferDataType;
    class Material;
    class RenderingComponent;
    class RenderingItem;

    class Renderer {
    public:
      explicit Renderer();

      std::shared_ptr<Camera> setCurrentCamera(std::shared_ptr<Camera>);
      std::shared_ptr<Camera> getCurrentCamera();
      std::shared_ptr<const Camera> getCurrentCamera() const;

      RenderingComponentPtr emplaceRenderingComponent(GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, size_t vertexCount);
      RenderingComponentPtr emplaceRenderingComponent(Common::Hash aHash, GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, size_t vertexCount);

      void render(float elapsedTime);
    private:
      SceneGraph mScene;
      RenderingComponentTable mRenderingComponents;
      std::unordered_map<Common::Hash, std::vector<RenderingComponentPtr>> mGameObjectIdRenderingComponents;

      static uint64_t mCount;
    };
  }
}