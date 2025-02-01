#ifndef MATERIAL_H
#define MATERIAL_H

#include "GraphicsContext.h"
#include "MaterialProperty.h"
#include "Shader.h"

#include <memory>
#include <string>
#include <unordered_map>


namespace K9ngineCore {
  namespace K9Graphics {
    class Material {
      using PropertiesContainer = std::unordered_map<MaterialProperty::PropertyIdType, std::shared_ptr<MaterialProperty>>;
    public:
      Material(const Shader&, const Shader&);

      void addOrSetProperty(std::shared_ptr<MaterialProperty>);
      bool hasProperty(const MaterialProperty::PropertyIdType&) const;
      std::shared_ptr<const MaterialProperty> getProperty(const MaterialProperty::PropertyIdType&) const;

      K9uint getProgramId() const { return mProgramId; }
      bool isCorrect() const { return mCorrect; }
    private:
      PropertiesContainer mProperties{};
      K9uint mProgramId{ 0 };
      bool mCorrect {false};
    };
  }
}

#endif
