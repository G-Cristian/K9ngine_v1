#include "RenderingItem.h"

#include "../Math/Math.h"
#include "Camera.h"

namespace K9ngineCore {
  namespace K9Graphics {
    RenderingItem::RenderingItem(RenderingComponentPtr renderingComponent, K9Math::Mat4& transfomr)
      : mRenderingComponent{renderingComponent}
      , mTransform{transfomr}
    {
    }

    const K9Math::Mat4& RenderingItem::getTransform() const
    {
      return mTransform;
    }

    const RenderingComponentPtr RenderingItem::getRenderingComponent() const
    {
      return mRenderingComponent;
    }

    void RenderingItem::render(double elapsedTime, std::shared_ptr<const Camera> camera) const
    {
      K9ASSERT(mRenderingComponent, "renderItem rendering component must not be null.");
      if (mRenderingComponent->isVisible()) {
        const auto& material = mRenderingComponent->getMaterial();
        if (material.use()) {
          const auto& modelMat = mTransform;
          const auto& viewMat = camera->getViewMatrix();
          material.checkAndSetModelMatrix(modelMat);
          material.checkAndSetViewMatrix(viewMat);
          material.checkAndSetModelViewMatrix(viewMat * modelMat);
          material.checkAndSetProjectionMatrix(camera->getProjectionMatrix());

          material.useProperties();

          const auto& vertexBufferObjectsData = mRenderingComponent->getVertexBufferObjectsData();
          for (int i{ 0 }; i != vertexBufferObjectsData.size(); i++) {
            material.setVertexAttribute(mRenderingComponent->getVertexBufferObjects()[i], vertexBufferObjectsData[i]);
          }

          GraphicsContext::enableDepthTest();
          GraphicsContext::setDepthFuncLessEqual();

          if (mRenderingComponent->getInstancesCount() > 1) {
            GraphicsContext::drawArraysInstanced(mRenderingComponent->getDrawMode(), mRenderingComponent->getFirtVertexIndex(), mRenderingComponent->getVerticesCount(), mRenderingComponent->getInstancesCount());
          }
          else {
            GraphicsContext::drawArrays(mRenderingComponent->getDrawMode(), mRenderingComponent->getFirtVertexIndex(), mRenderingComponent->getVerticesCount());
          }
        }
      }
    }
  }
}