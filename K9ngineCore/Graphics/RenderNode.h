#pragma once

#include "../Common/IObserver.h"
#include "../Common/TransformChangeEvent.h"
#include "../Handle.h"
#include "INode.h"
#include "RenderingComponent.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    class SceneGraph;
    class RenderNode :public INode
    {
    public:
      using RenderingComponentPtr = Memory::Handle<RenderingComponent>;
      using RenderingComponentConstPtr = Memory::Handle<const RenderingComponent>;
    public:
      RenderNode(SceneGraph&, RenderingComponentConstPtr);

      const RenderingComponentConstPtr getRenderingComponent() const;
    private:
      RenderingComponentConstPtr mRenderingComponent;
    };
  }
}