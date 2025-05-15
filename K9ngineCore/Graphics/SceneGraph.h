#pragma once

#include "INode.h"

#include <memory>
#include <queue>

namespace K9ngineCore {
  namespace K9Graphics {
    class ISceneGraphVisitor;
    class TransformNode;

    class SceneGraph {
    public:
      /********************************/
      /******* INNER CLASSES **********/

      /**********************************/

      /******** CONSTRUCTORS/DESTRUCTORS ************/

      SceneGraph();

      /**********************************/

      SceneGraph& operator=(const SceneGraph&) = delete;
      SceneGraph& operator=(SceneGraph&&) noexcept = delete;

      /******** MEMBER FUNCTIONS ************/

      void cleanDirty(INode*);
      void propagateDirtyUpwards();
      void propagateDirtyUpwards(INode*);
      void accept(ISceneGraphVisitor&);
      void setDirty(INode*);
    private:

      /**********************************/
    private:
      std::queue<INode*> mDirtyNodes{};
      std::shared_ptr<INode> mRoot;
    };
  }
}