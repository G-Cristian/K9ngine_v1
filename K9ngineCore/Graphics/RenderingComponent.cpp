#include "RenderingComponent.h"

#include "Camera.h"

#include "../Common/Hasher.h"
#include "../GameObject.h"
#include "../Handle.h"
#include "BufferDataType.h"
#include "GraphicsContext.h"
#include "Material.h"
#include "RenderNode.h"
#include "VertexBufferObjectData.h"

#include <memory>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    RenderingComponent::RenderingComponent(const Hash& id, GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, K9sizei verticesCount, K9int firtVertexIndex  /*= 0*/, DrawMode drawMode /*= DrawMode::K9_TRIANGLES*/)
      : mMaterial{material}
      //, mVertexBufferObjectsData()
      , mVertexBufferObjects{ std::make_unique<K9uint[]>(buffersData.size()) }
      , mGameObject{gameObject}
      , mDrawMode{drawMode}
      , mVerticesCount{verticesCount}
      , mFirtVertexIndex{firtVertexIndex}
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

    const std::shared_ptr<const RenderNode> RenderingComponent::getRenderNode() const
    {
      return mRenderNode.lock();
    }

    std::shared_ptr<RenderNode> RenderingComponent::getRenderNode()
    {
      return mRenderNode.lock();
    }

    void RenderingComponent::setRenderNode(RenderNodePtr renderNode)
    {
      mRenderNode = renderNode;
    }

    const GameObjectPtr RenderingComponent::getGameObject() const { return mGameObject; }

    void RenderingComponent::render(float elapsedTime, std::shared_ptr<const Camera> camera) const
    {
      if (mMaterial.use()) {
        const auto& modelMat = mGameObject->getTransform().getTransformMat4();
        const auto& viewMat = camera->getViewMatrix();
        mMaterial.checkAndSetModelMatrix(modelMat);
        mMaterial.checkAndSetViewMatrix(viewMat);
        mMaterial.checkAndSetModelViewMatrix(viewMat * modelMat);
        mMaterial.checkAndSetProjectionMatrix(camera->getProjectionMatrix());

        mMaterial.useProperties();

        for (int i{ 0 }; i != mVertexBufferObjectsData.size(); i++) {
          mMaterial.setVertexAttribute(mVertexBufferObjects[i], mVertexBufferObjectsData[i]);
        }

        GraphicsContext::enableDepthTest();
        GraphicsContext::setDepthFuncLessEqual();
        GraphicsContext::drawArrays(mDrawMode, mFirtVertexIndex, mVerticesCount);
      }
    }
  }
}