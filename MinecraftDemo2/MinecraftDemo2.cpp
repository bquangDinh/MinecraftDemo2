#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "Game.h"
#include "Terrain.h"
#include <thread>

using namespace std;

/*For Windows*/
const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Minecraft DDemo";

float deltaTime = 0.0f;
float lastTime = 0.0f;

void FrameBufferSizeCallback(GLFWwindow*, int, int);
void MousePosCallback(GLFWwindow*, double, double);
void KeyCallback(GLFWwindow*, int, int, int, int);

Game myGame(WIDTH, HEIGHT);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (window == NULL) {
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to init GLAD" << endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	//set callbacks
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	glfwSetCursorPosCallback(window, MousePosCallback);
	glfwSetKeyCallback(window, KeyCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//init game
	//load all resources, store them to memory
	myGame.Init();

	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		myGame.ProcessKeyInput(deltaTime);
		myGame.Update();
		myGame.Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	myGame.Destroy();
	return 0;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
	myGame.ProcessMouseInput(xPos, yPos);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			myGame.Keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			myGame.Keys[key] = false;
		}
	}
}