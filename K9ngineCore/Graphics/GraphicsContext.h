#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#ifdef K9_USE_VULKAN // K9_USE_VULKAN
#error "Vulkan not supported"
#elif defined K9_USE_DIRECTX // K9_USE_DIRECTX
#error "DirectX not supported"
#else
#include <Graphics/OpenGLContext.h>

namespace K9ngineCore {
  namespace K9Graphics {
    typedef GLchar K9char;
    typedef GLfloat K9float;
    typedef GLint K9int;
    typedef GLsizei K9sizei;
    typedef GLuint K9uint;

    typedef OpenGLShaderType ShaderType;
    typedef OpenGLContext GraphicsContext;
  }
}
#endif // End #else


#endif // !GRAPHICSCONTEXT_H
