#include "Game.h"

Game::Game(GLuint, GLuint)
{
}

Game::~Game()
{
}

void Game::Init()
{
	glEnable(GL_DEPTH_TEST);

#ifdef WIREFRAME_DEBUG
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif // WIREFRAME_DEBUG

	//load everything (texture, shader .v.v)
	TexturePiece grass_side = { "grass_side",3,0 };
	TexturePiece grass_top = { "grass_top",8,2 };
	TexturePiece grass_bottom = { "grass_bottom",2,0 };
	TexturePiece rock = { "rock",0,0 };
	TexturePiece pieces[] = { grass_side,grass_top,grass_bottom,rock };
	TextureManager::LoadTextureCoordAtlas("C:\\Users\\buiqu\\Downloads\\assets\\textures\\minecraft_textures_all_resized.png", 15, 15, "texture_atlas", pieces, 4);
	ShaderManager::LoadShaderProgram("vertexShader.vert", "fragmentShader.frag", "shader_program");

	chunk.GenerateTerrain("C:\\Users\\buiqu\\Downloads\\rsz_heightmap_1.bmp");
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
	glClearColor(1.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//adjust camer
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("projection", projection);
	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("view", mainCamera.getViewMatrix());

	chunk.Update();
}
