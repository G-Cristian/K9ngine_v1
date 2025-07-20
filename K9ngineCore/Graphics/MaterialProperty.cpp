#include "MaterialProperty.h"

#include "../Math/Math.h"

namespace K9ngineCore {
  namespace K9Graphics {
    template<typename T>
    T MaterialProperty::getValue() const {
      static_assert(false, "Unsupported type");
    }

    template<>
    K9Math::Mat4 MaterialProperty::getValue<K9Math::Mat4>() const
    {
      return getMat4();
    }

    template<>
    std::string MaterialProperty::getValue<std::string>() const
    {
      return getString();
    }

    template<>
    float MaterialProperty::getValue<float>() const
    {
      return getFloat();
    }

    template<>
    int MaterialProperty::getValue<int>() const
    {
      return getInt();
    }

    template<>
    bool MaterialProperty::getValue<bool>() const
    {
      return getBool();
    }
  }
}