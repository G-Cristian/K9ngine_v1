/*******************************************/
/****** Code based on learnopengl.com ******/
/*******************************************/

#include "Shader_old.h"

#include "K9Debug.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader_old::Shader_old(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		
		vertexCode = readFile(vShaderFile);
		fragmentCode = readFile(fShaderFile);

		vShaderFile.close();
		fShaderFile.close();
	}
	catch (std::ifstream::failure e) {
		K9ASSERT(false, (std::string("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: ") + e.what()).c_str());
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = compileShader(vShaderCode, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fShaderCode, GL_FRAGMENT_SHADER);

	ID = createLinkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader_old::use(){
	glUseProgram(ID);
}

void Shader_old::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader_old::setInt(const std::string & name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader_old::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader_old::setVec3(const std::string& name, const glm::vec3& vec) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader_old::setMat3(const std::string& name, const glm::mat3& matrix3) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix3));
}

void Shader_old::setMat4(const std::string& name, const glm::mat4& matrix4) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix4));
}

std::string Shader_old::readFile(std::ifstream& file) const {
	std::stringstream ss;
	ss << file.rdbuf();

	return ss.str();
}

unsigned int Shader_old::compileShader(const char* shaderCode, GLenum shaderType) const{
	unsigned int shader = 0;

	int success = 0;
	char infoLog[512];

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::stringstream ss;

		ss << "ERROR::SHADER::"	<<	(shaderType == GL_VERTEX_SHADER ? "VERTEX" :
											(shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT" : ""))
										<< "::COMPILATION_FAILED\n" << infoLog << std::endl;

		K9ASSERT(false, ss.str().c_str());
	}

	return shader;
}

unsigned int Shader_old::createLinkProgram(unsigned int vertexShader, unsigned int fragmentShader) const {
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	int success = 0;
	char infoLog[512];

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::stringstream ss;
		ss << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		K9ASSERT(false, ss.str().c_str());
	}

	return programID;
}
