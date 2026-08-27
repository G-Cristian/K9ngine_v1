#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include <glad/glad.h>

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../K9Debug.h"

namespace K9ngineCore {
  namespace K9Graphics {
    enum class OpenGLBoolValues : GLboolean {
      K9_FALSE = GL_FALSE,
      K9_TRUE = GL_TRUE
    };

    enum class OpenGLBufferDataUsage : GLenum {
      K9_STATIC_DRAW = GL_STATIC_DRAW
    };

    enum class OpenGLDepthFunctionMode : GLenum {
      K9_LEQUAL = GL_LEQUAL
    };

    enum class OpenGLDrawMode : GLenum {
      K9_POINTS = GL_POINTS,
      K9_TRIANGLES = GL_TRIANGLES,
      K9_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
      K9_TRIANGLE_FAN = GL_TRIANGLE_FAN,
      K9_TRIANGLE_ADJACENCY = GL_TRIANGLES_ADJACENCY,
      K9_TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
      K9_LINES = GL_LINES,
      K9_LINE_STRIP = GL_LINE_STRIP,
      K9_LINE_LOOP = GL_LINE_LOOP,
      K9_LINES_ADJACENCY = GL_LINES_ADJACENCY,
      K9_LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
      K9_PATCHES = GL_PATCHES
    };

    enum class OpenGLFrontFaceMode : GLenum {
      K9_CW = GL_CW,
      K9_CCW = GL_CCW
    };

    enum class OpenGLShaderType : GLenum{
      K9_VERTEX_SHADER = GL_VERTEX_SHADER,
      K9_FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    enum class OpenGLTargetBuffer : GLenum {
      K9_ARRAY_BUFFER = GL_ARRAY_BUFFER
    };

    enum class OpenGLTargetTexture : GLenum {
      K9_TEXTURE_2D = GL_TEXTURE_2D
    };

    enum class OpenGLTextureSampler : GLenum {
      K9_TEXTURE0 = GL_TEXTURE0
    };

    enum class OpenGLTypeEnum : GLenum {
      K9_FLOAT = GL_FLOAT
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

      static void bindArrayBuffer(GLuint buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
      }

      static void bindBuffer(OpenGLTargetBuffer targetBuffer, GLuint buffer) {
        glBindBuffer(std::to_underlying(targetBuffer), buffer);
      }

      static void bindTexture(OpenGLTargetTexture target, GLuint texture) {
        glBindTexture(std::to_underlying(target), texture);
      }

      static void bindVertexArray(GLuint vertexArray) {
        glBindVertexArray(vertexArray);
      }

      template<class T>
      static void bufferArrayBufferData(const T* data, unsigned int n, OpenGLBufferDataUsage usage) {
        glBufferData(GL_ARRAY_BUFFER, n * sizeof(T), data, std::to_underlying(usage));
      }

      template<class T>
      static void bufferData(OpenGLTargetBuffer targetBuffer, const T* data, unsigned int n, OpenGLBufferDataUsage usage) {
        glBufferData(std::to_underlying(targetBuffer), n * sizeof(T), data, std::to_underlying(usage));
      }

      static void clearColor() {
        glClear(GL_COLOR_BUFFER_BIT);
      }

      static void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
      }

      static void clearDepth() {
        glClear(GL_DEPTH_BUFFER_BIT);
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

      static void drawArrays(OpenGLDrawMode mode, GLint first, GLsizei count) {
        glDrawArrays(std::to_underlying(mode), first, count);
      }

      static void drawArraysInstanced(OpenGLDrawMode mode, GLint first, GLsizei count, GLsizei instanceCount) {
        glDrawArraysInstanced(std::to_underlying(mode), first, count, instanceCount);
      }

      static void drawArraysTriangles(GLint first, GLsizei count) {
        glDrawArrays(GL_TRIANGLES, first, count);
      }

      static void enableCullFace() {
        glEnable(GL_CULL_FACE);
      }

      static void enableDepthTest() {
        glEnable(GL_DEPTH_TEST);
      }

      static void enableVertexAttribArray(GLuint index) {
        glEnableVertexAttribArray(index);
      }

      static void generateBuffers(GLsizei n, GLuint* buffers) {
        glGenBuffers(n, buffers);
      }

      static void generateVertexArrays(GLsizei n, GLuint* VAOs) {
        glGenVertexArrays(n, VAOs);
      }

      static GLint getMajorVersion() {
        GLint major{ 0 };
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        return major;
      }

      static GLint getMinorVersion() {
        GLint minor{ 0 };
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        return minor;
      }

      static std::string getProgramInfoLog(GLuint program, GLuint length) {
        std::string log;

        if (length > 0) {
          char* chLog = (char*)malloc(length);
          int chWrittn{ 0 };
          glGetProgramInfoLog(program, length, &chWrittn, chLog);
          if (chLog != NULL) {
            log = std::string(chLog);
          }
          free(chLog);
        }

        return log;
      }

      static GLint getProgramInfoLogLength(GLuint program) {
        GLint length{ 0 };
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        return length;
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

      static GLint getUniformLocation(GLuint program, std::string_view name) {
        return glGetUniformLocation(program, name.data());
      }

      static std::string getVersionString() {
        const GLubyte* version = glGetString(GL_VERSION);
        if (!version) {
          return std::string{};
        }

        return std::string(reinterpret_cast<const char*>(version));
      }

      static bool isProgramLinkStatusOk(GLuint program) {
        GLint status{};
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        return status == 1;
      }

      static bool isShaderCompileStatusOk(GLuint shader) {
        GLint status{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        return status == 1;
      }

      static void linkProgram(GLuint program) {
        glLinkProgram(program);
      }

      static void setActiveTexture(OpenGLTextureSampler texture) {
        glActiveTexture(std::to_underlying(texture));
      }

      static void setClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        glClearColor(red, green, blue, alpha);
      }

      static void setDepthFuncMode(OpenGLDepthFunctionMode depthFunctionMode) {
        glDepthFunc(std::to_underlying(depthFunctionMode));
      }

      static void setDepthFuncLessEqual() {
        glDepthFunc(GL_LEQUAL);
      }

      static void setFrontFaceMode(OpenGLFrontFaceMode frontFace) {
        glFrontFace(std::to_underlying(frontFace));
      }

      static void setFrontFaceCCW() {
        glFrontFace(GL_CCW);
      }

      static void setFrontFaceCW() {
        glFrontFace(GL_CW);
      }

      static void setUniform1f(GLint location, GLfloat value) {
        glUniform1f(location, value);
      }

      static void setUniformMatrix4fv(GLint location, GLsizei count, OpenGLBoolValues transpose, const GLfloat* value) {
        glUniformMatrix4fv(location, count, std::to_underlying(transpose), value);
      }

      static void setVertexAttributePointer(GLuint index, GLint size, OpenGLTypeEnum type, OpenGLBoolValues normalized, GLsizei stride, const void* pointer) {
        glVertexAttribPointer(index, size, std::to_underlying(type), std::to_underlying(normalized), stride, pointer);
      }

      static void setViewport(GLint x, GLint y, GLsizei width, GLsizei height)
      {
        glViewport(x, y, width, height);
      }

      static void shaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
        glShaderSource(shader, count, string, length);
      }

      static void useProgram(GLuint program) {
        glUseProgram(program);
      }
    };
  }
}

#endif // !OPENGLCONTEXT_H
