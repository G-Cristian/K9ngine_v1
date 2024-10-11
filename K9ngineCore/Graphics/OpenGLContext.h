#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include <glad/glad.h>

namespace K9ngineCore {
  namespace K9Graphics {
    class OpenGLContext {
    public:
      static int init() {
        return gladLoadGL();
      }

      static void setClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
      }

      static void clearColor() {
        glClear(GL_COLOR_BUFFER_BIT);
      }

      static void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
      }
    };
  }
}

#endif // !OPENGLCONTEXT_H
