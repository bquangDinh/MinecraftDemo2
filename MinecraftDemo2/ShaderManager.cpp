#include "ShaderManager.h"

std::map<std::string, Shader> ShaderManager::Shaders;
std::map<std::string, ShaderProgram> ShaderManager::ShaderPrograms;

Shader ShaderManager::LoadShader(const char* shaderFile, GLenum shaderType, std::string name)
{
	Shader shader = Shader(shaderFile, shaderType);
	Shaders[name] = shader;
	return Shaders[name];
}

Shader ShaderManager::GetShader(std::string name)
{
	return Shaders[name];
}

ShaderProgram ShaderManager::LoadShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile, std::string name)
{
	Shader vertexShader = Shader(vertexShaderFile, GL_VERTEX_SHADER);
	Shader fragmentShader = Shader(fragmentShaderFile, GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram = ShaderProgram(vertexShader, fragmentShader);
	ShaderPrograms[name] = shaderProgram;
	return ShaderPrograms[name];
}

ShaderProgram ShaderManager::LoadShaderProgram(Shader vertexShader, Shader fragmentShader, std::string name)
{
	ShaderProgram shaderProgram = ShaderProgram(vertexShader, fragmentShader);
	ShaderPrograms[name] = shaderProgram;
	return ShaderPrograms[name];
}

ShaderProgram ShaderManager::LoadShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, std::string name)
{
	ShaderProgram shaderProgram = ShaderProgram(vertexShader, fragmentShader);
	ShaderPrograms[name] = shaderProgram;
	return ShaderPrograms[name];
}

ShaderProgram ShaderManager::GetShaderProgram(std::string name)
{
	return ShaderPrograms[name];
}

void ShaderManager::ClearShaders()
{
	for (auto iter : Shaders) {
		glDeleteShader(iter.second.ID);
	}

	for (auto iter : ShaderPrograms) {
		glDeleteProgram(iter.second.ID);
	}
}
