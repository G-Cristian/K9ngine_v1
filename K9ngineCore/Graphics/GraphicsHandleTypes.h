#pragma once

#ifndef RENDERINGCOMPONENTS_COUNT
#define RENDERINGCOMPONENTS_COUNT 0
#endif // !RENDERINGCOMPONENTS_COUNT

#include "../Handle.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    class BufferDataType;
    class RenderingComponent;

    using BufferDataTypePtr = std::shared_ptr<BufferDataType>;
    //using BufferDataTypeConstPtr = const BufferDataTypePtr;
    using RenderingComponentTable = Memory::HandleTable<RenderingComponent, RENDERINGCOMPONENTS_COUNT>;
    using RenderingComponentPtr = RenderingComponentTable::handle_type;
    using ConstRenderingComponentPtr = RenderingComponentTable::const_handle_type;
    //using RenderingComponentConstPtr = const RenderingComponentPtr;
  }
}