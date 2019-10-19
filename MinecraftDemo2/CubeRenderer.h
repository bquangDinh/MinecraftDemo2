#pragma once
#include <glad/glad.h>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CubeUtils.h"
#include "Quad.h"
#include <vector>

typedef struct {
	float x, y, z;
} Vertex;

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void AddQuadToVBO(Quad);
	void GenerateVBO();
	void Render();
private:
	GLuint VAO;
	vector<float> verticles;
	vector<unsigned int> indicates;
	int count = -1;
	int faceCount = 0;
	GLuint EBO;
	const float* getCubeTexCoord(int side, int type);
};

