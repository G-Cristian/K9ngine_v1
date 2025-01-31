#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "../K9Debug.h"

#include <glad/glad.h>
#include <string>
#include <utility>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {

    enum class OpenGLShaderType : GLenum{
      K9_VERTEX_SHADER = GL_VERTEX_SHADER,
      K9_FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    class OpenGLContext {
    public:
      // Glad
      
      static int init() {
        return gladLoadGL();
      }

      // OpenGL

      static void attachShader(GLuint program, GLuint shader) {
        glAttachShader(program, shader);
      }

      static void clearColor() {
        glClear(GL_COLOR_BUFFER_BIT);
      }

      static void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
      }

      static void compileShader(GLuint shader) {
        glCompileShader(shader);
      }

      static GLuint createProgram() {
        return glCreateProgram();
      }

      static GLuint createShader(OpenGLShaderType shaderType) {
        return glCreateShader(std::to_underlying(shaderType));
      }

      static bool checkAndLogErrors() {
        bool foundErrors = false;
        int error = glGetError();
        while (error != GL_NO_ERROR) {
          foundErrors = true;
          LOG_ADD_TAB();
          LOG_ERROR(std::format("glError: {}", error));
          LOG_REMOVE_TAB();
          error = glGetError();
        }

        return foundErrors;
      }

      static bool isShaderCompileStatusOk(GLuint shader) {
        GLint status{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        return status == 1;
      }

      static std::string getShaderInfoLog(GLuint shader, GLuint length) {
        std::string log;
        
        if (length > 0) {
          char* chLog = (char*)malloc(length);
          int chWrittn{ 0 };
          glGetShaderInfoLog(shader, length, &chWrittn, chLog);
          if (chLog != NULL) {
            log = std::string(chLog);
          }
          free(chLog);
        }

        return log;
      }

      static GLint getShaderInfoLogLength(GLuint shader) {
        GLint length{ 0 };
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        return length;
      }

      static void linkProgram(GLuint program) {
        glLinkProgram(program);
      }

      static void setClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
      }

      static void shaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
        glShaderSource(shader, count, string, length);
      }
    };
  }
}

#endif // !OPENGLCONTEXT_H
