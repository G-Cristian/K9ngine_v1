#include "BufferDataType.h"

#include "GraphicsContext.h"

#include <string>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    BufferDataType::BufferDataType(const std::string& name, const std::vector<float>& data, K9int size, TargetBuffer targetBuffer, BufferDataUsage dataUsage, TypeEnum type, BoolValues normalized, K9sizei stride)
      : mData{data}
      , mName{name}
      , mTargetBuffer{targetBuffer}
      , mDataUsage{dataUsage}
      , mType{type}
      , mNormalized{ normalized }
      , mStride{stride}
      , mSize(size)
    {
    }

    const std::vector<float>& BufferDataType::getData() const { return mData; }
    const std::string& BufferDataType::getName() const { return mName; }
    TargetBuffer BufferDataType::getTargetBuffer() const { return mTargetBuffer; }
    BufferDataUsage BufferDataType::getDataUsage() const { return mDataUsage; }
    TypeEnum BufferDataType::getType() const { return mType; }
    BoolValues BufferDataType::isNormalized() const { return mNormalized; }
    K9sizei BufferDataType::getStride() const { return mStride; }
    K9int BufferDataType::getSize() const { return mSize; }
  }
}