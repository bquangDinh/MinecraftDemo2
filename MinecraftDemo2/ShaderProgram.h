#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	GLuint ID;
	
	ShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	ShaderProgram(GLuint shaderProgram);
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	ShaderProgram();

	void Use();

	//Set value
	void SetMatrix4(const char* name, glm::mat4 matrix);
	void SetVector2(const char* name, glm::vec2 vec2);
};

