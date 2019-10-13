#pragma once
#include "Cube.h"
#include <glad/glad.h>
#include "ShaderManager.h"
#include "TextureManager.h"
#include <vector>

typedef struct {
	float x, y, z;
} Vertex;

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void AddVerticleToVBO(Cube::CUBESIDE side,glm::vec3 position, float* texUV);
	void GenerateVBO();
	void Render();
private:
	GLuint VAO;
	vector<float> verticles;
	vector<unsigned int> indicates;
	int count = -1;
	int faceCount = 0;
	GLuint EBO;
	const float* getCudeSide(Cube::CUBESIDE side);
};

