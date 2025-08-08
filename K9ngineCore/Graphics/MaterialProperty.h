#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <memory>
#include <string>
#include <string_view>

#include "../Math/Math.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class ShaderProgram;

    class MaterialProperty {
    public:
      using PropertyIdType = std::string;
      MaterialProperty(const PropertyIdType& id) :
        mId(id) {
      }

      virtual ~MaterialProperty() = default;

      virtual void useProperty(std::shared_ptr<ShaderProgram>) const = 0;

      const PropertyIdType& getId() const { return mId; }

      template<typename T>
      T getValue() const;
      virtual void setMat4(const K9Math::Mat4&) = 0;
      virtual void setString(std::string_view) = 0;
      virtual void setFloat(float) = 0;
      virtual void setInt(int) = 0;
      virtual void setBool(bool) = 0;
    protected:
      virtual K9Math::Mat4 getMat4() const = 0;
      virtual std::string getString() const = 0;
      virtual float getFloat() const = 0;
      virtual int getInt() const = 0;
      virtual bool getBool() const = 0;

      PropertyIdType mId;
    };
  }
}

#endif // !MATERIALPROPERTY_H
