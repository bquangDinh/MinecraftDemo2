#pragma once
#include <glad/glad.h>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CubeUtils.h"
#include "Quad.h"
#include <vector>
#include <string>

class CubeRenderer
{
public:
	static std::string shader;

	bool isReadyToUse = false;
	CubeRenderer();
	~CubeRenderer();

	void AddQuadToVBO(Quad, int, int, bool);

	void GenerateVBO();
	void GenerateVAO();
	void Render();
private:
	GLuint VAO;
	GLuint EBO;
	GLuint VBO;
	vector<float> verticles;
	vector<unsigned int> indicates;

	int count = -1;
	int faceCount = 0;
	const float* getCubeTexCoord(int side, int type);
	void increaseFaceCount();
	void printReport();
};

