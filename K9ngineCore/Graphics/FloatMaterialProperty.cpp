#include <format>
#include <type_traits>

#include "../K9Debug.h"

#include "FloatMaterialProperty.h"

#include "GraphicsContext.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"

namespace K9ngineCore {
  namespace K9Graphics {
    FloatMaterialProperty::FloatMaterialProperty(const PropertyIdType& id)
      : MaterialProperty(id)
    {
    }

    FloatMaterialProperty::FloatMaterialProperty(const PropertyIdType& id, float value)
      : MaterialProperty(id)
      , mValue(value)
    {
    }

    void FloatMaterialProperty::useProperty(std::shared_ptr<ShaderProgram> program) const
    {
      auto location = GraphicsContext::getUniformLocation(program->getProgramId(), mId);
      if (location != -1) {
        GraphicsContext::setUniform1f(location, mValue);
      }
      else {
        K9ASSERT(false, std::format("Uniform location not found for property: {}", mId).c_str());
      }
    }

    [[maybe_unused]] void FloatMaterialProperty::setMat4(const K9Math::Mat4& value)
    {
      K9ASSERT(false, "FloatMaterialProperty::setMat4() not supported.");
    }

    [[maybe_unused]] void FloatMaterialProperty::setString(std::string_view)
    {
      K9ASSERT(false, "FloatMaterialProperty::setString() not supported.");
    }

    void FloatMaterialProperty::setFloat(float value)
    {
      mValue = value;
    }

    void FloatMaterialProperty::setInt(int value)
    {
      setFloat(static_cast<float>(value));
    }

    [[maybe_unused]] void FloatMaterialProperty::setBool(bool)
    {
      K9ASSERT(false, "FloatMaterialProperty::setBool() not supported.");
    }

    K9Math::Mat4 FloatMaterialProperty::getMat4() const
    {
      K9ASSERT(false, "FloatMaterialProperty::getMat4() not supported.");
      return K9Math::identityMat4();
    }

    [[maybe_unused]] std::string FloatMaterialProperty::getString() const
    {
      return std::format("{}", mValue);
    }

    [[maybe_unused]] float FloatMaterialProperty::getFloat() const
    {
      return mValue;
    }

    [[maybe_unused]] int FloatMaterialProperty::getInt() const
    {
      return static_cast<int>(mValue);
    }

    [[maybe_unused]] bool FloatMaterialProperty::getBool() const
    {
      K9ASSERT(false, "FloatMaterialProperty::getBool() not supported.");
      return false;
    }
  }
}