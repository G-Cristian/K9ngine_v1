#pragma once

#include "GraphicsContext.h"
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    struct VertexBufferObjectData {
    public:
      std::string name{};
      TargetBuffer targetBuffer{ TargetBuffer::K9_ARRAY_BUFFER };
      BufferDataUsage dataUsage{ BufferDataUsage::K9_STATIC_DRAW };
      TypeEnum type{ TypeEnum::K9_FLOAT };
      BoolValues isNormalized{ BoolValues::K9_FALSE };
      K9sizei stride{ 0 };
      K9int size{ 3 };
    };
  }
}