#pragma once
#include "GLM.h"
#include "ShaderManager.h"
#include <iostream>

class LightingManager
{
private:
	bool hasInitialized = false;
	bool hasWarning = false;
	glm::mat4 lightProjection, lightView;

public:
	float ambientStrength;
	glm::vec3 lightPos, lightColor;

	LightingManager();
	~LightingManager();

	void Initialize(float ambientStrength, glm::vec3 lightColor, glm::vec3 lightPos);
	glm::mat4 getLightSpaceMatrix();

	void Update(float time);
};

