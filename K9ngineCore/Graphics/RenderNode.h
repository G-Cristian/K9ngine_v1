#pragma once

#include "../Common/IObserver.h"
#include "../Common/TransformChangeEvent.h"
#include "../Handle.h"
#include "GraphicsHandleTypes.h"
#include "INode.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    class ISceneGraphVisitor;
    class RenderingComponent;
    class SceneGraph;
    class RenderNode :public INode
    {
    public:
      RenderNode(SceneGraph&, RenderingComponentPtr);

      void accept(ISceneGraphVisitor&) override final;
      const RenderingComponentPtr getRenderingComponent() const;
    private:
      RenderingComponentPtr mRenderingComponent;
    };
  }
}