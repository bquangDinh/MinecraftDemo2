#include "Shader.h"

Shader::Shader(const char* shaderFile, GLenum shaderType)
{
	std::string shaderCodeStr = File::readFile(shaderFile);
	const char* shaderCode = shaderCodeStr.c_str();

	//compile shader
	this->ID = glCreateShader(shaderType);
	glShaderSource(this->ID, 1, &shaderCode, NULL);
	glCompileShader(this->ID);

	//check shader compiling
	int success;
	const int LOG_BUFFER = 512;
	char infoLog[LOG_BUFFER];

	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->ID, LOG_BUFFER, NULL, infoLog);
		cout << "ERROR:::SHADER::COMPILING::" << infoLog << endl;
	}
	else {
		cout << "SHADER::COMPILING::SUCCESS" << endl;
	}
}

Shader::Shader()
{
	this->ID = 0;
}
