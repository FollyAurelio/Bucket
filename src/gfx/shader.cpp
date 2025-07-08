#include "shader.h"

Shader::Shader(std::string vertexCode, std::string fragmentCode){
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	handle = glCreateProgram();
	glAttachShader(handle, vertex);
	glAttachShader(handle, fragment);
	glLinkProgram(handle);
	// print linking errors if any
	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(handle);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(handle, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(handle, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(handle, name.c_str()), value);
}

void Shader::setMatrix4(const std::string &name, glm::mat4 m) const
{
	glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setVector3(const std::string &name, glm::vec3 v) const
{
	glUniform3f(glGetUniformLocation(handle, name.c_str()), v.x, v.y, v.z);
}
