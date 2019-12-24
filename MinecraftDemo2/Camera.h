#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float cameraSpeed = 20.5f;

	//align turning around speed ==> not too fast && not too slow
	float sensitivity = 0.5f;

	float pitch = 0.0f; // look up and down
	const float PITCH_LIMIT = 89.0f;
	
	float yaw = -90.0f; // look left and right

	// make the first mouse position at the center of screen
	float lastMouseXPos = 400.0f; // WIDTH / 2
	float lastMouseYPos = 300.0f; // HEIGHT / 2

	bool firstAround = false;

public:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::mat4 getViewMatrix();

	/*Moving Functions*/
	void MoveForward(float);
	void MoveBackWard(float);
	void GoLeft(float);
	void GoRight(float);
	void TurnAround(float, float);
};

