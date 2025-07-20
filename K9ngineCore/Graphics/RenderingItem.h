#pragma once

#include "../Handle.h"
#include "../Math/Math.h"
#include "GraphicsHandleTypes.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class RenderingComponent;

    class RenderingItem {
    public:
      RenderingItem(const RenderingComponentPtr, K9Math::Mat4&);

      const K9Math::Mat4& getTransform() const;
      const RenderingComponentPtr getRenderingComponent() const;
    private:
      RenderingComponentPtr mRenderingComponent;
      K9Math::Mat4 mTransform;
    };
  }
}