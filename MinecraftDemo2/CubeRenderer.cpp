#include "CubeRenderer.h"
	
CubeRenderer::CubeRenderer()
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::AddQuadToVBO(Quad quad)
{
	if (quad.direction == FRONTSIDE || quad.direction == TOPSIDE || quad.direction == LEFTSIDE) {
		this->indicates.push_back(3 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(0 + 4 * this->faceCount);

		this->indicates.push_back(3 + 4 * this->faceCount);
		this->indicates.push_back(2 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
	}
	else {
		this->indicates.push_back(0 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(3 + 4 * this->faceCount);

		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(2 + 4 * this->faceCount);
		this->indicates.push_back(3 + 4 * this->faceCount);
	}

	this->faceCount++;

	const float* texCoordPointer = NULL;
	int side = quad.direction;
	int type = quad.type;

	if (side == 0 || side == 1 || side == 2 || side == 3) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 4) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_top").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 5) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_bottom").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}

	if (texCoordPointer == NULL) {
		texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
	}

	this->verticles.push_back(quad.p1.x);
	this->verticles.push_back(quad.p1.y);
	this->verticles.push_back(quad.p1.z);
	//cout << "x: " << quad.p1.x << " y: " << quad.p1.y << " z: " << quad.p1.z << endl;

	this->verticles.push_back(*(texCoordPointer + 0));
	this->verticles.push_back(*(texCoordPointer + 1));
	//cout << "u: " << *(texCoordPointer + 0) << " v: " << *(texCoordPointer + 1) << endl;

	this->verticles.push_back(quad.p2.x);
	this->verticles.push_back(quad.p2.y);
	this->verticles.push_back(quad.p2.z);
	//cout << "x: " << quad.p2.x << " y: " << quad.p2.y << " z: " << quad.p2.z << endl;

	this->verticles.push_back(*(texCoordPointer + 2));
	this->verticles.push_back(*(texCoordPointer + 3));

	this->verticles.push_back(quad.p3.x);
	this->verticles.push_back(quad.p3.y);
	this->verticles.push_back(quad.p3.z);
	//cout << "x: " << quad.p3.x << " y: " << quad.p3.y << " z: " << quad.p3.z << endl;

	this->verticles.push_back(*(texCoordPointer + 4));
	this->verticles.push_back(*(texCoordPointer + 5));

	this->verticles.push_back(quad.p4.x);
	this->verticles.push_back(quad.p4.y);
	this->verticles.push_back(quad.p4.z);
	//cout << "x: " << quad.p4.x << " y: " << quad.p4.y << " z: " << quad.p4.z << endl;

	this->verticles.push_back(*(texCoordPointer + 6));
	this->verticles.push_back(*(texCoordPointer + 7));
}

void CubeRenderer::GenerateVBO()
{
	//cout << "Generate VBO" << endl;

	glGenVertexArrays(1,&this->VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->verticles.size() * sizeof(float), &this->verticles[0], GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicates.size() * sizeof(unsigned int), &this->indicates[0], GL_STATIC_DRAW);

	//for position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//for uv
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void CubeRenderer::Render()
{
	TextureManager::GetTexture("texture_atlas").Bind();
	ShaderManager::GetShaderProgram("shader_program").Use();
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indicates.size(), GL_UNSIGNED_INT, (void*)0);
}

const float* CubeRenderer::getCubeTexCoord(int side, int type)
{
	const float* texCoordPointer = NULL;

	if (side == 0 || side == 1 || side == 2 || side == 3) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 4) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_top").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 5) {
		if (type == 1) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_bottom").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoordPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}

	if (texCoordPointer == NULL) {
		texCoordPointer = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
	}

	return texCoordPointer;
}

