#pragma once

#include "GraphicsContext.h"
#include "MaterialProperty.h"
#include "Shader.h"

#include <memory>
#include <string>
#include <unordered_map>


namespace K9ngineCore {
  namespace K9Graphics {
    class ShaderProgram {
    public:
      ShaderProgram(const Shader&, const Shader&);

      void use() const;
      K9uint getProgramId() const { return mProgramId; }
      bool isCorrect() const { return mCorrect; }
    private:
      K9uint mProgramId{ 0 };
      bool mCorrect{ false };
    };
  }
}