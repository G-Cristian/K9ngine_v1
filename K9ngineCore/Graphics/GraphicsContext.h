#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#ifdef K9_USE_OPENGL

#include <Graphics/OpenGLContext.h>

namespace K9ngineCore {
  namespace K9Graphics {
    typedef GLfloat K9float;
    typedef GLint K9int;
    typedef GLuint K9uint;

    typedef OpenGLContext GraphicsContext;
  }
}

#elif K9_USE_VULKAN // K9_USE_VULKAN
#error "Vulkan not supported"
#elif K9_USE_DIRECTX // K9_USE_DIRECTX
#error "DirectX not supported"
#else
#error "Proyect must define a graphics api (K9_USE_OPENGL/K9_USE_VULKAN/K9_USE_DIRECTX)"
#endif // End K9_USE_DIRECTX


#endif // !GRAPHICSCONTEXT_H
