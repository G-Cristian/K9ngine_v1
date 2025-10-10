#pragma once

#include <memory>
#include <vector>

#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "SceneGraph.h"

#include "../CommonHandleTypes.h"
#include "../Common/Hasher.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class BufferDataType;
    class Material;
    class RenderingComponent;
    class RenderingItem;

    class Renderer {
    public:
      explicit Renderer();
      ~Renderer();

      void clear();

      std::shared_ptr<Camera> setCurrentCamera(std::shared_ptr<Camera>);
      std::shared_ptr<Camera> getCurrentCamera();
      std::shared_ptr<const Camera> getCurrentCamera() const;

      RenderingComponentPtr emplaceRenderingComponent(GameObjectPtr gameObject, const Material& material, const std::vector<RenderingComponent::BufferDataTypePtr>& buffersData, K9sizei vertexCount, K9sizei instancesCount = 1);
      RenderingComponentPtr emplaceRenderingComponent(Common::Hash aHash, GameObjectPtr gameObject, const Material& material, const std::vector<RenderingComponent::BufferDataTypePtr>& buffersData, K9sizei vertexCount, K9sizei instancesCount = 1);

      ConstRenderingComponentPtr getRenderingComponent(const Common::Hash& renderingComponentHash) const;
      RenderingComponentPtr getRenderingComponent(const Common::Hash& renderingComponentHash);

      ConstRenderingComponentPtr getRenderingComponent(const Common::Hash& gameObjectId, const Common::Hash& renderingComponentHash) const;
      RenderingComponentPtr getRenderingComponent(const Common::Hash& gameObjectId, const Common::Hash& renderingComponentHash);

      void propagateDirtySceneGraphNodes();

      void render(float elapsedTime);
    private:
      SceneGraph mScene;
      RenderingComponentTable mRenderingComponents;
      std::unordered_map<Common::Hash, std::vector<RenderingComponentPtr>> mGameObjectIdRenderingComponents;

      static uint64_t mCount;
    };
  }
}