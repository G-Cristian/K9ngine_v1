#include <format>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../K9Debug.h"

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
#include "../World.h"

namespace K9ngineCore {
  namespace K9Graphics {

    uint64_t Renderer::mCount{ 0 };

    Renderer::Renderer()
      : mScene{ }
      , mRenderingComponents{ }
    {
    }

    Renderer::~Renderer()
    {
      clear();
    }

    void Renderer::clear()
    {
      mScene.clear();
      mRenderingComponents.clear();
      mGameObjectIdRenderingComponents.clear();
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

    RenderingComponentPtr Renderer::emplaceRenderingComponent(GameObjectPtr gameObject, const Material& material, const std::vector<RenderingComponent::BufferDataTypePtr>& buffersData, K9sizei vertexCount, K9sizei instancesCount/* = 1*/)
    {
      using namespace Common;

      return emplaceRenderingComponent(Common::hashString(std::format("{}", mCount++)), gameObject, material, buffersData, vertexCount, instancesCount);
    }

    RenderingComponentPtr Renderer::emplaceRenderingComponent(Common::Hash aHash, GameObjectPtr gameObject, const Material& material, const std::vector<RenderingComponent::BufferDataTypePtr>& buffersData, K9sizei vertexCount, K9sizei instancesCount/* = 1*/)
    {

      uint64_t uid = Common::hashToUInt64(aHash);
      auto renderingComponent = mRenderingComponents.getHandle(mRenderingComponents.createHandle(uid, aHash, gameObject, material, buffersData, vertexCount, instancesCount));
      auto transformNode = mScene.createOrGetTransformNode(gameObject);

      mGameObjectIdRenderingComponents[gameObject->getId()].push_back(renderingComponent);
      auto renderNode = mScene.createRenderNode(renderingComponent);
      mScene.linkNode(renderNode, transformNode);

      return renderingComponent;
    }

    ConstRenderingComponentPtr Renderer::getRenderingComponent(const Common::Hash& renderingComponentHash) const
    {
      uint64_t uid = Common::hashToUInt64(renderingComponentHash);
      return mRenderingComponents.findHandle(uid);
    }

    RenderingComponentPtr Renderer::getRenderingComponent(const Common::Hash& renderingComponentHash)
    {
      uint64_t uid = Common::hashToUInt64(renderingComponentHash);
      return mRenderingComponents.findHandle(uid);
    }

    ConstRenderingComponentPtr Renderer::getRenderingComponent(const Common::Hash& gameObjectId, const Common::Hash& renderingComponentHash) const
    {
      auto it = mGameObjectIdRenderingComponents.find(gameObjectId);
      if (it != mGameObjectIdRenderingComponents.cend()) {
        for (auto& renderingComponent : it->second) {
          if (renderingComponent && renderingComponent->getId() == renderingComponentHash) {
            return renderingComponent;
          }
        }
      }

      return RenderingComponentTable::ConstNullHandle;
    }

    RenderingComponentPtr Renderer::getRenderingComponent(const Common::Hash& gameObjectId, const Common::Hash& renderingComponentHash)
    {
      auto it = mGameObjectIdRenderingComponents.find(gameObjectId);
      if (it != mGameObjectIdRenderingComponents.end()) {
        for (auto& renderingComponent : it->second) {
          if (renderingComponent && renderingComponent->getId() == renderingComponentHash) {
            return renderingComponent;
          }
        }
      }

      return RenderingComponentTable::NullHandle;
    }

    void Renderer::propagateDirtySceneGraphNodes()
    {
      mScene.propagateDirtyUpwards();
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
            renderingItem->render(elapsedTime, mScene.getCurrentCamera());
          }
        }
      }
    }
  }
}