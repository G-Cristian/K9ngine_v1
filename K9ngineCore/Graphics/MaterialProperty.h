#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <string>

namespace K9ngineCore {
  namespace K9Graphics {

    class MaterialProperty {
    public:
      using PropertyIdType = std::string;
      MaterialProperty(const PropertyIdType& id) :
        mId(id) {
      }

      const PropertyIdType& getId() const { return mId; }

      virtual void* getValue() const = 0;
      virtual void setInt(int) = 0;
    protected:
      PropertyIdType mId;
    };
  }
}

#endif // !MATERIALPROPERTY_H
