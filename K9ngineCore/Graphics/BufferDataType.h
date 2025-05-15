#pragma once

#include "GraphicsContext.h"

#include <string>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class BufferDataType {
    public:
      BufferDataType(const std::string&, const std::vector<float>&, K9int, TargetBuffer, BufferDataUsage, TypeEnum, BoolValues, K9sizei);

      const std::vector<float>& getData() const;
      const std::string& getName() const;
      TargetBuffer getTargetBuffer() const;
      BufferDataUsage getDataUsage() const;
      TypeEnum getType() const;
      BoolValues isNormalized() const;
      K9sizei getStride() const;
      K9int getSize() const;
    private:
      std::vector<float> mData;
      std::string mName;
      TargetBuffer mTargetBuffer;
      BufferDataUsage mDataUsage;
      TypeEnum mType;
      BoolValues mNormalized;
      K9sizei mStride;
      K9int mSize;
    };
  }
}