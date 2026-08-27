#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#ifdef K9_USE_VULKAN // K9_USE_VULKAN
#error "Vulkan not supported"
#elif defined K9_USE_DIRECTX // K9_USE_DIRECTX
#error "DirectX not supported"
#else
#include "OpenGLContext.h"

namespace K9ngineCore {
  namespace K9Graphics {
    typedef GLchar K9char;
    typedef GLfloat K9float;
    typedef GLint K9int;
    typedef GLsizei K9sizei;
    typedef GLuint K9uint;

    using BoolValues = OpenGLBoolValues;
    using BufferDataUsage = OpenGLBufferDataUsage;
    using DepthFunctionMode = OpenGLDepthFunctionMode;
    using DrawMode = OpenGLDrawMode;
    using FrontFaceMode = OpenGLFrontFaceMode;
    using ShaderType = OpenGLShaderType;
    using TargetBuffer = OpenGLTargetBuffer;
    using TargetTexture = OpenGLTargetTexture;
    using TextureSampler = OpenGLTextureSampler;
    using TypeEnum = OpenGLTypeEnum;

    typedef OpenGLContext GraphicsContext;
  }
}
#endif // End #else


#endif // !GRAPHICSCONTEXT_H
