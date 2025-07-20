#include "RenderingItem.h"

#include "../Math/Math.h"

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
  }
}