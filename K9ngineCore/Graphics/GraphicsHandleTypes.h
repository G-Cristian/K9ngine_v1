#pragma once

#ifndef RENDERINGCOMPONENTS_COUNT
#define RENDERINGCOMPONENTS_COUNT 0
#endif // !RENDERINGCOMPONENTS_COUNT

#include "../Handle.h"
#include "RenderingComponent.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    using RenderingComponentTable = Memory::HandleTable<RenderingComponent, RENDERINGCOMPONENTS_COUNT>;
    using RenderingComponentPtr = RenderingComponentTable::handle_type;
    using ConstRenderingComponentPtr = RenderingComponentTable::const_handle_type;
    //using RenderingComponentConstPtr = const RenderingComponentPtr;
  }
}