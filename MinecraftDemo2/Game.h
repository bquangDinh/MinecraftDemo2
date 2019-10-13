#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CubeRenderer.h"
#include "Camera.h"
#include "CubeChunk.h"

#define WIREFRAME_DEBUG

enum GameState {
	RUNNING,
	PAUSE
};

class Game
{
public:
	GameState currentState;
	GLboolean Keys[1024];
	GLuint Width, Height;
	Camera mainCamera;
	CubeChunk chunk;
	Game(GLuint, GLuint);
	~Game();

	//Load Textures and Shaders
	void Init();

	void Destroy();

	// Process input from user <Keyboard, mouse>
	void ProcessKeyInput(float);
	void ProcessMouseInput(double,double);

	void Update();

	//Render to screen
	void Render();
};

