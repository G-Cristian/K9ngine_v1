#include "Mat4MaterialProperty.h"

#include "GraphicsContext.h"
#include "K9Debug.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"

#include <type_traits>

namespace K9ngineCore {
  namespace K9Graphics {
    Mat4MaterialProperty::Mat4MaterialProperty(const PropertyIdType& id)
      : MaterialProperty(id)
    {
    }

    Mat4MaterialProperty::Mat4MaterialProperty(const PropertyIdType& id, const Mat4Type& value)
      : MaterialProperty(id)
      , mValue(value)
    {
    }

    Mat4MaterialProperty::Mat4MaterialProperty(const PropertyIdType& id, const Mat4Type& value, K9sizei count)
      : MaterialProperty(id)
      , mValue(value) 
      , mCount(count)
    {
    }

    
    Mat4MaterialProperty::Mat4MaterialProperty(const PropertyIdType& id, const Mat4Type& value, K9sizei count, bool transpose)
      : MaterialProperty(id)
      , mValue(value)
      , mCount(count) 
      , mTranspose(transpose ? BoolValues::K9_TRUE : BoolValues::K9_FALSE)
    {
    }

    void Mat4MaterialProperty::useProperty(std::shared_ptr<ShaderProgram> program) const
    {
      auto location = GraphicsContext::getUniformLocation(program->getProgramId(), mId);
      if (location != -1) {
        GraphicsContext::setUniformMatrix4fv(location, mCount, mTranspose, K9Math::asValuePtr(mValue));
      }
      else {
        K9ASSERT(false, std::format("Uniform location not found for property: {}", mId).c_str());
      }
    }

    void Mat4MaterialProperty::setMat4(const Mat4Type& value)
    {
      mValue = value;
    }

    [[maybe_unused]] void Mat4MaterialProperty::setString(std::string_view)
    {
      K9ASSERT(false, "Mat4MaterialProperty::setString() not supported.");
    }

    void Mat4MaterialProperty::setFloat(float value)
    {
      mValue = K9Math::initMat4(value);
    }

    void Mat4MaterialProperty::setInt(int value)
    {
      setFloat(static_cast<float>(value));
    }

    [[maybe_unused]] void Mat4MaterialProperty::setBool(bool)
    {
      K9ASSERT(false, "Mat4MaterialProperty::setBool() not supported.");
    }

    Mat4MaterialProperty::Mat4Type Mat4MaterialProperty::getMat4() const
    {
      return mValue;
    }

    [[maybe_unused]] std::string Mat4MaterialProperty::getString() const
    {
      K9ASSERT(false, "Mat4MaterialProperty::getString() not supported.");
      return std::string{};
    }

    [[maybe_unused]] float Mat4MaterialProperty::getFloat() const
    {
      K9ASSERT(false, "Mat4MaterialProperty::getFloat() not supported.");
      return 0.0f;
    }

    [[maybe_unused]] int Mat4MaterialProperty::getInt() const
    {
      K9ASSERT(false, "Mat4MaterialProperty::getInt() not supported.");
      return 0;
    }

    [[maybe_unused]] bool Mat4MaterialProperty::getBool() const
    {
      K9ASSERT(false, "Mat4MaterialProperty::getBool() not supported.");
      return false;
    }
  }
}