#include "RenderingComponent.h"

#include "../Common/Hasher.h"
#include "../GameObject.h"
#include "../Handle.h"
#include "BufferDataType.h"
#include "GraphicsContext.h"
#include "Material.h"
#include "VertexBufferObjectData.h"

#include <memory>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    RenderingComponent::RenderingComponent(const Hash& id, GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypeConstPtr>& buffersData)
      : mMaterial{material}
      , mVertexBufferObjectsData{}
      , mVertexBufferObjects{ std::make_unique<K9uint[]>(buffersData.size()) }
      , mGameObject{gameObject}
      , mId{id}
    {
      GraphicsContext::generateVertexArrays(1, &mVAO);
      GraphicsContext::bindVertexArray(mVAO);
      GraphicsContext::generateBuffers(buffersData.size(), mVertexBufferObjects.get());
      
      mVertexBufferObjectsData.reserve(buffersData.size());
      for (int i = 0; i != buffersData.size(); i++) {
        mVertexBufferObjectsData.push_back(
          {
            buffersData[i]->getName()
          , buffersData[i]->getTargetBuffer()
          , buffersData[i]->getDataUsage()
          , buffersData[i]->getType()
          , buffersData[i]->isNormalized()
          , buffersData[i]->getStride()
          , buffersData[i]->getSize()
          });
        GraphicsContext::bindBuffer(buffersData[i]->getTargetBuffer(), mVertexBufferObjects[i]);
        GraphicsContext::bufferData(buffersData[i]->getTargetBuffer(), buffersData[i]->getData().data(), buffersData[i]->getData().size(), buffersData[i]->getDataUsage());
      }
    }

    const Hash& RenderingComponent::getId() const { return mId; }

    const RenderingComponent::GameObjectPtr RenderingComponent::getGameObject() const { return mGameObject; }

    void RenderingComponent::render(float elapsedTime) const
    {
      // TODO: call graphics context drawing functions, something like:
      if (mMaterial.use()) {
        for (int i{ 0 }; i != mVertexBufferObjectsData.size(); i++) {
          mMaterial.setVertexAttribute(mVertexBufferObjects[i], mVertexBufferObjectsData[i]);
          //...
          //draw()
        }
      }

      // Also store properties such as targetbuffer and size (3 in the above code)
    }
  }
}