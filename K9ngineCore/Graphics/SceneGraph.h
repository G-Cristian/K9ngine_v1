#pragma once

#ifndef RENDERINGCOMPONENTS_COUNT
#define RENDERINGCOMPONENTS_COUNT 0
#endif // !RENDERINGCOMPONENTS_COUNT

#include "CommonHandleTypes.h"
#include "GraphicsHandleTypes.h"
#include "INode.h"

#include "../Common/Hasher.h"

#include <cstdint>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class Camera;
    class ISceneGraphVisitor;
    class RenderingComponent;
    class RenderNode;
    class TransformNode;

    class SceneGraph {
    public:
      /********************************/
      /******* INNER CLASSES **********/

      /**********************************/

      /******** CONSTRUCTORS/DESTRUCTORS ************/

      explicit SceneGraph();

      /**********************************/

      SceneGraph& operator=(const SceneGraph&) = delete;
      SceneGraph& operator=(SceneGraph&&) noexcept = delete;

      /******** MEMBER FUNCTIONS ************/

      void cleanDirty(INode*);
      void propagateDirtyUpwards();
      void propagateDirtyUpwards(INode*);
      void accept(ISceneGraphVisitor&);
      void setDirty(INode*);

      std::shared_ptr<TransformNode> createOrGetTransformNode(GameObjectPtr);
      std::shared_ptr<RenderNode> createRenderNode(RenderingComponentPtr);
      std::shared_ptr<INode> linkNode(std::shared_ptr<INode> node, std::shared_ptr<INode> parent);

      std::shared_ptr<Camera> setCurrentCamera(std::shared_ptr<Camera>);
      std::shared_ptr<Camera> getCurrentCamera();
      std::shared_ptr<const Camera> getCurrentCamera() const;
    private:

      /**********************************/
    private:
      std::queue<INode*> mDirtyNodes;
      std::unordered_map<Common::Hash, std::shared_ptr<TransformNode>> mGameObjectIdTransformNode;
      std::shared_ptr<Camera> mCurrentCamera;
      std::shared_ptr<INode> mRoot;
    };
  }
}