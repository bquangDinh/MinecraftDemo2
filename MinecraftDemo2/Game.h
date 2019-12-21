#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CubeRenderer.h"
#include "Camera.h"
#include "ChunkManager.h"
#include <string>

//#define WIREFRAME_DEBUG
#define ENABLE_CULLING_MODE
#define ENABLE_DEPTH_TEST

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
	ChunkManager* chunkManager;
	Game(GLuint width, GLuint height);
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
	void ViewRender();
};

