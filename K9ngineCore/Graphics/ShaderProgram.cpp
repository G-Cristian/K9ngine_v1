#include "ShaderProgram.h"

#include "GraphicsContext.h"

#include "../K9Debug.h"

#include <format>
#include <string>

namespace K9ngineCore {
  namespace K9Graphics {
    ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
      K9ASSERT(vertexShader.isCorrect(), "Vertex shader incorrect.");
      K9ASSERT(fragmentShader.isCorrect(), "Vertex shader incorrect.");

      mCorrect = vertexShader.isCorrect() && fragmentShader.isCorrect();
      if (mCorrect) {
        mProgramId = GraphicsContext::createProgram();
        GraphicsContext::attachShader(mProgramId, vertexShader.getShaderId());
        GraphicsContext::attachShader(mProgramId, fragmentShader.getShaderId());
        GraphicsContext::linkProgram(mProgramId);
        GraphicsContext::checkAndLogErrors();
        if (!GraphicsContext::isProgramLinkStatusOk(mProgramId)) {
          mCorrect = false;
          K9int programInfoLogLength = GraphicsContext::getProgramInfoLogLength(mProgramId);
          auto errorMsg = std::format("Program {} link failed.\n {}", mProgramId, GraphicsContext::getProgramInfoLog(mProgramId, programInfoLogLength));
          K9ASSERT(mCorrect, errorMsg.c_str());
        }
      }
    }

    void ShaderProgram::use() const {
      K9ASSERT(isCorrect(), std::format("Shader program {} is incorrect.", mProgramId).c_str());
      GraphicsContext::useProgram(mProgramId);
    }
  }
}