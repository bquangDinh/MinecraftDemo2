#pragma once
#include <glad/glad.h>
#include "File.h"
class Shader
{
public:
	GLuint ID;
	Shader(const char* shaderFile, GLenum shaderType);
	Shader();
};

