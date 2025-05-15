#pragma once

#include "../Handle.h"
#include "../Math/Math.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class RenderingComponent;

    class RenderingItem {
    public:
      using RenderingComponentPtr = Memory::Handle<RenderingComponent>;
      using RenderingComponentConstPtr = Memory::Handle<const RenderingComponent>;

      RenderingItem(RenderingComponentConstPtr, K9Math::Mat4&);

      const K9Math::Mat4& getTransform() const;
      const RenderingComponentConstPtr getRenderingComponent() const;
    private:
      RenderingComponentConstPtr mRenderingComponent;
      K9Math::Mat4 mTransform;
    };
  }
}