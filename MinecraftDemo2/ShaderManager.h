#pragma once
#include <string>
#include <map>
#include "Shader.h"
#include "ShaderProgram.h"

class ShaderManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, ShaderProgram> ShaderPrograms;

	static Shader LoadShader(const char* shaderFile, GLenum shaderType, std::string name);
	static Shader GetShader(std::string name);

	static ShaderProgram LoadShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile, std::string name);
	static ShaderProgram LoadShaderProgram(Shader vertexShader, Shader fragmentShader, std::string name);
	static ShaderProgram LoadShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, std::string name);

	static ShaderProgram GetShaderProgram(std::string name);

	static void ClearShaders();

private:
	ShaderManager() {}
};

