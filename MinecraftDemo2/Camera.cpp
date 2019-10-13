#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(this->cameraPos, this->cameraFront + this->cameraPos, this->cameraUp);
	return view;
}

void Camera::MoveForward(float deltaTime)
{
	float speed = this->cameraSpeed * deltaTime;
	this->cameraPos = this->cameraPos + this->cameraFront * speed;
}

void Camera::MoveBackWard(float deltaTime)
{
	float speed = this->cameraSpeed * deltaTime;
	this->cameraPos = this->cameraPos - this->cameraFront * speed;
}

void Camera::GoLeft(float deltaTime)
{
	float speed = this->cameraSpeed * deltaTime;
	glm::vec3 cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));
	this->cameraPos = this->cameraPos - cameraRight * speed;
}

void Camera::GoRight(float deltaTime)
{
	float speed = this->cameraSpeed * deltaTime;
	glm::vec3 cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));
	this->cameraPos = this->cameraPos + cameraRight * speed;
}

void Camera::TurnAround(float mouseXPos, float mouseYPos)
{
	if (this->firstAround == false) {
		this->lastMouseXPos = mouseXPos;
		this->lastMouseYPos = mouseYPos;
		this->firstAround = true;
	}

	//need to note here in notebook
	float offsetX = mouseXPos - this->lastMouseXPos;
	float offsetY = mouseYPos - this->lastMouseYPos;

	this->lastMouseXPos = mouseXPos;
	this->lastMouseYPos = mouseYPos;

	offsetX *= this->sensitivity;
	offsetY *= this->sensitivity;

	//update yaw and pitch value
	this->yaw += offsetX;
	this->pitch += offsetY;

	if (this->pitch > this->PITCH_LIMIT) this->pitch = this->PITCH_LIMIT;
	if (this->pitch < this->PITCH_LIMIT * (-1)) this->pitch = this->PITCH_LIMIT * (-1);

	glm::vec3 front;
	front.x = glm::cos(glm::radians(this->yaw)) + glm::cos(glm::radians(this->pitch));
	front.y = glm::sin(glm::radians(this->pitch));
	front.z = glm::cos(glm::radians(this->pitch)) + glm::sin(glm::radians(this->yaw));

	this->cameraFront = glm::normalize(front);
}
