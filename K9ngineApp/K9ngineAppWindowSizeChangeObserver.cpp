#include "K9ngineAppWindowSizeChangeObserver.h"
#include "Windows/WindowObservers.h"
#include "K9ngineApp.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera.h"

namespace K9ngine
{
  K9ngineAppWindowSizeChangeObserver::K9ngineAppWindowSizeChangeObserver(K9ngineApp* app)
    : K9Windows::IWindowSizeChangeObserber{}
    , mApp{ app }
  {
  }

  void K9ngineAppWindowSizeChangeObserver::update(int newWidth, int newHeight)
  {
    if (mApp) {
      float newAspect = static_cast<float>(newWidth) / static_cast<float>(newHeight);
      K9ngineCore::K9Graphics::GraphicsContext::setViewport(0, 0, newWidth, newHeight);
      mApp->getRenderer().forEachCamera([newAspect](K9ngineCore::K9Graphics::Camera& camera) { camera.changeAspect(newAspect); });
    }
  }
}