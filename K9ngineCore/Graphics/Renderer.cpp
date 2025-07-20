#include "Renderer.h"

#include "GraphicsContext.h"
#include "GraphicsHandleTypes.h"
#include "INode.h"
#include "ISceneGraphVisitor.h"
#include "RenderingComponent.h"
#include "RenderingItem.h"
#include "RenderNode.h"
#include "SceneGraph.h"
#include "SceneGraphRenderVisitor.h"
#include "TransformNode.h"

#include "../CommonHandleTypes.h"
#include "../Common/Hasher.h"
#include "../GameObject.h"
#include "../Handle.h"
#include "../K9Debug.h"
#include "../World.h"

#include <format>
#include <memory>
#include <unordered_map>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {

    uint64_t Renderer::mCount{ 0 };

    Renderer::Renderer()
      : mScene{}
      , mRenderingComponents{ }
    {
    }

    std::shared_ptr<Camera> Renderer::setCurrentCamera(std::shared_ptr<Camera> camera)
    {
      return mScene.setCurrentCamera(camera);
    }

    std::shared_ptr<Camera> Renderer::getCurrentCamera() 
    {
      return mScene.getCurrentCamera();
    }

    std::shared_ptr<const Camera> Renderer::getCurrentCamera() const
    {
      return mScene.getCurrentCamera();
    }

    RenderingComponentPtr Renderer::emplaceRenderingComponent(GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, size_t vertexCount)
    {
      using namespace Common;

      return emplaceRenderingComponent(Common::hashString(std::format("{}", mCount++)), gameObject, material, buffersData, vertexCount);
    }

    RenderingComponentPtr Renderer::emplaceRenderingComponent(Common::Hash aHash, GameObjectPtr gameObject, const Material& material, const std::vector<BufferDataTypePtr>& buffersData, size_t vertexCount)
    {

      uint64_t uid = Common::hashToUInt64(aHash);
      auto renderingComponent = mRenderingComponents.getHandle(mRenderingComponents.createHandle(uid, new RenderingComponent(aHash, gameObject, material, buffersData, vertexCount)));
      auto transformNode = mScene.createOrGetTransformNode(gameObject);

      mGameObjectIdRenderingComponents[gameObject->getId()].push_back(renderingComponent);
      auto renderNode = mScene.createRenderNode(renderingComponent);
      mScene.linkNode(renderNode, transformNode);

      return renderingComponent;
    }

    void Renderer::render(float elapsedTime)
    {
      SceneGraphRenderVisitor sceneGraphVisitor{ mScene };
      mScene.accept(sceneGraphVisitor);
      auto renderingItems = sceneGraphVisitor.getRenderingItems();
      K9ASSERT(renderingItems, "Rendering items must not be null.");
      if (renderingItems) {
        // TODO: sort renderingItems as apropriate
        // TODO: render the renderingItems.
        GraphicsContext::clearColor();
        GraphicsContext::clearDepth();
        for (auto renderingItem : *renderingItems) {
          K9ASSERT(renderingItem, "Rendering item must not be null.");
          if (renderingItem) {
            K9ASSERT(renderingItem->getRenderingComponent(), "renderItem rendering component must not be null.");
            renderingItem->getRenderingComponent()->render(elapsedTime, mScene.getCurrentCamera());
          }
        }
      }
    }
  }
}