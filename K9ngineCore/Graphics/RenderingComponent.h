#pragma once

#include "../Common/Hasher.h"
#include "../CommonHandleTypes.h"
#include "../Handle.h"
#include "BufferDataType.h"
#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "Material.h"
#include "VertexBufferObjectData.h"

#include <memory>
#include <vector>

namespace K9ngineCore {
  class GameObject;
  namespace K9Graphics {
    class Camera;
    class RenderNode;
    class RenderingComponent {
    public:
      using RenderNodePtr = std::weak_ptr<RenderNode>;
      using Hash = Common::Hash;

      RenderingComponent(const Hash& id, GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, K9sizei verticesCount, K9sizei instancesCount = 1, K9int firtVertexIndex = 0, DrawMode drawMode = DrawMode::K9_TRIANGLES);

      const Hash& getId() const;

      const std::shared_ptr<const RenderNode> getRenderNode() const;
      std::shared_ptr<RenderNode> getRenderNode();
      void setRenderNode(RenderNodePtr renderNode);

      Material& getMaterial() { return mMaterial; }
      const Material& getMaterial() const { return mMaterial; }
      
      ConstGameObjectPtr getGameObject() const;

      void setVisible(bool visible);
      bool isVisible() const;
      
      void render(double elapsedTime, std::shared_ptr<const Camera>) const;
    private:
      Material mMaterial;
      std::vector<VertexBufferObjectData> mVertexBufferObjectsData;
      std::unique_ptr<K9uint[]> mVertexBufferObjects;
      RenderNodePtr mRenderNode;
      GameObjectPtr mGameObject;
      Hash mId{};
      DrawMode mDrawMode{DrawMode::K9_TRIANGLES};
      K9sizei mVerticesCount{};
      K9sizei mInstancesCount{1};
      K9int mFirtVertexIndex{0};
      K9uint mVAO = {};
      bool mVisible{true};
    };
  }
}