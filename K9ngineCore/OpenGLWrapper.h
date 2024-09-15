#ifndef OPENGLWRAPPER_H
#define OPENGLWRAPPER_H

#include <glad/glad.h>

namespace K9ngineCore {
  class OpenGLWrapper {
  public:
    static int  init() {
      return gladLoadGL();
    }
  };
}

#endif // !OPENGLWRAPPER_H
