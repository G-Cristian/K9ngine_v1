#include "Shader.h"

#include "GraphicsContext.h"

#include <format>
#include <string>

namespace K9ngineCore {
  namespace K9Graphics {
    Shader::Shader(ShaderType shaderType, const K9char* content)
      : mType(shaderType) {
      mShaderId = GraphicsContext::createShader(shaderType);
      GraphicsContext::shaderSource(mShaderId, 1, &content, NULL);
      GraphicsContext::compileShader(mShaderId);
      GraphicsContext::checkAndLogErrors();
      if (!GraphicsContext::isShaderCompileStatusOk(mShaderId)) {
        mCorrect = false;
        logError();
      }
    }

    void Shader::logError() const {
      LOG_ADD_TAB();
      K9int shaderInfoLogLength = GraphicsContext::getShaderInfoLogLength(mShaderId);
      LOG_ERROR(std::format("Shader {} compilation failed.\n {}", mShaderId, GraphicsContext::getShaderInfoLog(mShaderId, shaderInfoLogLength)));
      LOG_REMOVE_TAB();
    }
  }
}