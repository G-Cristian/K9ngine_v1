#pragma once

#include "../Common/Hasher.h"
#include "../Handle.h"
#include "BufferDataType.h"
#include "GraphicsContext.h"
#include "Material.h"

#include <memory>
#include <vector>

namespace K9ngineCore {
  class GameObject;
  struct VertexBufferObjectData;
  namespace K9Graphics {
    class RenderingComponent {
    public:
      using GameObjectPtr = Memory::Handle<GameObject>;
      using BufferDataTypePtr = Memory::Handle<BufferDataType>;
      using BufferDataTypeConstPtr = Memory::Handle<const BufferDataType>;
      using Hash = Common::Hash;

      RenderingComponent(const Hash&, GameObjectPtr, const Material&, const std::vector<BufferDataTypeConstPtr>&);

      const Hash& getId() const;
      
      const GameObjectPtr getGameObject() const;
      
      void render(float elapsedTime) const;
    private:
      Material mMaterial;
      std::vector<VertexBufferObjectData> mVertexBufferObjectsData;
      std::unique_ptr<K9uint[]> mVertexBufferObjects;
      GameObjectPtr mGameObject;
      Hash mId{};
      K9uint mVAO = {};
    };
  }
}