#include "Game.h"

Game::Game(GLuint, GLuint)
{
}

Game::~Game()
{
}

void Game::Init()
{
	double firstTime = glfwGetTime();
	cout << "Initialize..." << endl;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

#ifdef WIREFRAME_DEBUG
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif // WIREFRAME_DEBUG

	//load everything (texture, shader .v.v)
	TexturePiece grass_side = { "grass_side",12,15 };
	TexturePiece grass_top = { "grass_top",7,13 };
	TexturePiece grass_bottom = { "grass_bottom",13,15 };
	TexturePiece rock = { "rock",14,15 };
	TexturePiece pieces[] = { grass_side,grass_top,grass_bottom,rock };
	TextureManager::LoadTextureCoordAtlas("C:\\Users\\buiqu\\Downloads\\assets\\textures\\imageedit_2_3831088975.png", 15, 15, "texture_atlas", pieces, 4);
	ShaderManager::LoadShaderProgram("vertexShader.vert", "fragmentShader.frag", "shader_program");

	chunk.Generate();
	double lastTime = glfwGetTime();
	cout << "Done !" << endl;
	cout << "Time to process: " << lastTime - firstTime << "s" << endl;
}

void Game::Destroy()
{
	TextureManager::ClearTextures();
	ShaderManager::ClearShaders();
}

void Game::ProcessKeyInput(float deltaTime)
{
	if (this->Keys[GLFW_KEY_W]) {
		this->mainCamera.MoveForward(deltaTime);
	}
	if (this->Keys[GLFW_KEY_S]) {
		this->mainCamera.MoveBackWard(deltaTime);
	}
	if (this->Keys[GLFW_KEY_A]) {
		this->mainCamera.GoLeft(deltaTime);
	}
	if (this->Keys[GLFW_KEY_D]) {
		this->mainCamera.GoRight(deltaTime);
	}
}

void Game::ProcessMouseInput(double xPos, double yPos)
{
	mainCamera.TurnAround(xPos, yPos);
}

void Game::Update()
{
}

void Game::Render()
{
	glClearColor(0.2f, 0.6f, 0.85f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//adjust camer
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 200.0f);

	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("projection", projection);
	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("view", mainCamera.getViewMatrix());

	chunk.Update();
}
