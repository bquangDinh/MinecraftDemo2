#pragma once
#include <glad/glad.h>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CubeUtils.h"
#include "Quad.h"
#include <vector>
#include "GLM.h"

class MeshBuilder
{
public:
	MeshBuilder();
	~MeshBuilder();

	void AddQuad(Quad quad, int width, int height, bool backface);

	void GenerateVBO();
	void CleanUp();
	void Render();
private:
	GLuint VAO;
	std::vector<float> verticles;
	std::vector<unsigned int> indicates;
	int faceCount;
	bool readyToRender;

	void addPointV3(glm::vec3 point);
	void addPointV2(glm::vec2 point);
	void addIndicates(bool backface, int offset);
	int getTextureIndex(int type, int face);
	void printReport();
};

