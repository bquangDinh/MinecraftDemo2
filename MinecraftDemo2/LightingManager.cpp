#include "LightingManager.h"

LightingManager::LightingManager()
{
	ambientStrength = 0.2f;
	lightPos = glm::vec3(-10.0f, 20.0f, 0.0f);
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	lightProjection = glm::ortho(0.0f, 50.0f, 0.0f, 50.0f, 1.0f, 20.0f);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

LightingManager::~LightingManager()
{
}

void LightingManager::Initialize(float ambientStrength, glm::vec3 lightColor, glm::vec3 lightPos)
{
	this->ambientStrength = ambientStrength;
	this->lightColor = lightColor;
	this->lightPos = lightPos;
	hasInitialized = true;
}

glm::mat4 LightingManager::getLightSpaceMatrix()
{
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	return lightSpaceMatrix;
}

void LightingManager::Update(float time)
{
	if (!hasInitialized) {
		if (!hasWarning) {
			std::cout << "[WARNING] Lighting system has not been initialized yet ! Used default values." << endl;
			hasWarning = true;
		}
	}

	ShaderManager::GetShaderProgram("shader_program").SetVector3("lightPos", lightPos);
	ShaderManager::GetShaderProgram("shader_program").SetVector3("lightColor", lightColor);
	ShaderManager::GetShaderProgram("shader_program").SetFloat("ambientStregth", ambientStrength);
}
