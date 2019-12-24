#include "Game.h"

Game::Game(GLuint width, GLuint height)
{
	Width = width;
	Height = Height;
	currentState = GameState::RUNNING;
	chunkManager = new ChunkManager(glm::vec3(10, 1, 10), glm::vec3(16, 32, 16));
	lightingManager = new LightingManager();
	shadow = new Shadow();

	if (chunkManager == nullptr) {
#ifdef DEBUG
		cout << "Cannot create a new Chunk Manager. Something goes wrong !!!" << endl;
#endif // DEBUG
	}

	if (lightingManager == nullptr) {
#ifdef DEBUG
		cout << "Cannot create a new Lighting Manager. Something goes wrong !!!" << endl;
#endif // DEBUG
	}
}

Game::~Game()
{
}

void Game::Init()
{
	double firstTime = glfwGetTime();
	cout << "Initialize..." << endl;

#ifdef ENABLE_DEPTH_TEST
	glEnable(GL_DEPTH_TEST);
#endif

#ifdef ENABLE_CULLING_MODE
	glEnable(GL_CULL_FACE);
#endif

	glEnable(GL_CULL_FACE);

#ifdef WIREFRAME_DEBUG
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

	//load everything (texture, shader .v.v)

	ShaderManager::LoadShaderProgram("vertexShader.vert", "fragmentShader.frag", "shader_program");
	ShaderManager::LoadShaderProgram("ShadowVertexShader.vert", "ShadowFragmentShader.frag", "shadow_shader_program");

	TextureManager::LoadTextureArray("C:\\Users\\buiqu\\Downloads\\assets\\textures\\T5XQv5z.png", true, "texture_array");

	chunkManager->Initialize();
	lightingManager->Initialize(0.2f, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(32.0f, 25.7f, 60.5f));
	shadow->Initialize();

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

	//lightingManager->lightPos = mainCamera.cameraPos;
	//cout << "x: " << mainCamera.cameraPos.x << " y: " << mainCamera.cameraPos.y << " z: " << mainCamera.cameraPos.z << endl;

	ShaderManager::GetShaderProgram("shader_program").Use();

	lightingManager->Update(glfwGetTime());

	//shadow here
	glCullFace(GL_FRONT);
	ShaderManager::GetShaderProgram("shadow_shader_program").Use();
	ShaderManager::GetShaderProgram("shadow_shader_program").SetMatrix4("lightSpaceMatrix", lightingManager->getLightSpaceMatrix());
	
	MeshBuilder::shader = "shadow_shader_program";

	glBindFramebuffer(GL_FRAMEBUFFER, shadow->FBO);
	shadow->shadowMap->Bind();

	//first Meshing
	chunkManager->Update();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	MeshBuilder::shader = "shader_program";

	//render as usual here
	glCullFace(GL_BACK);
	ShaderManager::GetShaderProgram("shader_program").Use();

	glActiveTexture(GL_TEXTURE1);
	shadow->shadowMap->Bind();
	glActiveTexture(GL_TEXTURE0);

	//adjust camer
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 200.0f);

	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("projection", projection);
	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("lightSpaceMatrix", lightingManager->getLightSpaceMatrix());
	ShaderManager::GetShaderProgram("shader_program").SetMatrix4("view", mainCamera.getViewMatrix());

	lightingManager->Update(glfwGetTime());
	
	chunkManager->Update();
}

void Game::ViewRender()
{
	
}
