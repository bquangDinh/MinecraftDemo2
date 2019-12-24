#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include <iostream>

class Shadow
{
private:
	bool hasInitialized = false;
public:
	Texture2D* shadowMap;
	GLuint FBO;

	Shadow();
	~Shadow();

	void Initialize();
	void Update();
};

