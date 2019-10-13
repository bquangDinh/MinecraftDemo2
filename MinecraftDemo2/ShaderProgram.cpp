#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	//attaching and linking
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	glLinkProgram(this->ID);

	//check program linking
	int success;
	const int LOG_BUFFER = 512;
	char infoLog[LOG_BUFFER];

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, LOG_BUFFER, NULL, infoLog);
		cout << "ERROR::PROGRAM::LINKING::" << infoLog << endl;
	}
	else {
		cout << "PROGRAM::LINKING::SUCCESS" << endl;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
{
	//attaching and linking
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader.ID);
	glAttachShader(this->ID, fragmentShader.ID);
	glLinkProgram(this->ID);

	//check program linking
	int success;
	const int LOG_BUFFER = 512;
	char infoLog[LOG_BUFFER];

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, LOG_BUFFER, NULL, infoLog);
		cout << "ERROR::PROGRAM::LINKING::" << infoLog << endl;
	}
	else {
		cout << "PROGRAM::LINKING::SUCCESS" << endl;
		glDeleteShader(vertexShader.ID);
		glDeleteShader(fragmentShader.ID);
	}
}

ShaderProgram::ShaderProgram(GLuint shaderProgram)
{
	this->ID = shaderProgram;
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	Shader vertexShader(vertexFile,GL_VERTEX_SHADER);
	Shader fragmentShader(fragmentFile, GL_FRAGMENT_SHADER);

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader.ID);
	glAttachShader(this->ID, fragmentShader.ID);
	glLinkProgram(this->ID);

	//check program linking
	int success;
	const int LOG_BUFFER = 512;
	char infoLog[LOG_BUFFER];

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, LOG_BUFFER, NULL, infoLog);
		cout << "ERROR::PROGRAM::LINKING::" << infoLog << endl;
	}
	else {
		cout << "PROGRAM::LINKING::SUCCESS" << endl;
		glDeleteShader(vertexShader.ID);
		glDeleteShader(fragmentShader.ID);
	}
}

ShaderProgram::ShaderProgram()
{
	this->ID = 0;
}

void ShaderProgram::Use()
{
	glUseProgram(this->ID);
}

void ShaderProgram::SetMatrix4(const char* name, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(this->ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetVector2(const char* name, glm::vec2 vec2)
{
	unsigned int location = glGetUniformLocation(this->ID, "texCoord");
	glUniform2f(location, vec2.x, vec2.y);
}


