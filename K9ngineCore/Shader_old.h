#ifndef SHADER_H
#define SHADER_H

/***************************************/
/****** Code from learnopengl.com ******/
/***************************************/

//#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

class Shader_old {
public:
	unsigned int ID;
	Shader_old(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3& vec) const;
	void setMat3(const std::string& name, const glm::mat3& matrix3) const;
	void setMat4(const std::string& name, const glm::mat4& matrix4) const;
private:
	std::string readFile(std::ifstream&)const;
	unsigned int compileShader(const char* shaderCode, GLenum shaderType) const;
	unsigned int createLinkProgram(unsigned int vertexShader, unsigned int fragmentShader) const;
};

#endif
