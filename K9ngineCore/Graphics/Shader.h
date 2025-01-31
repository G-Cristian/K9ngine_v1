#ifndef SHADER_H
#define SHADER_H

#include "GraphicsContext.h"

namespace K9ngineCore {
  namespace K9Graphics {
    class Shader {
    public:
      Shader(ShaderType shaderType, const K9char* content);
      K9uint getShaderId() const { return mShaderId; }
      ShaderType getType() const { return mType; }
      bool isCorrect() const { return mCorrect; }
    private:
      void logError() const;
      K9uint mShaderId { 0 };
      ShaderType mType;
      bool mCorrect { true };
    };
  }
}

#endif // !SHADER_H
