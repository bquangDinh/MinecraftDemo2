#include "CubeRenderer.h"
	
CubeRenderer::CubeRenderer()
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::AddVerticleToVBO(Cube::CUBESIDE side, glm::vec3 position, float* texUV)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	const float* sideData = this->getCudeSide(side);

	int posIndex = -1;
	int texCoordIndex = -1;

	float* texCoord = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;

	const unsigned int* indicate = NULL;

	if (side == Cube::CUBESIDE::FRONT || side == Cube::CUBESIDE::TOP || side == Cube::CUBESIDE::RIGHT) {
		indicate = Cube::FRONT_INDICATES;
	}
	else {
		indicate = Cube::BACK_INDICATES;
	}

	for (int i = 0; i < 4; i++) {
		// 6 verticles of a cube ==> (x,y,z)(u,v) x 6
		float x = *(sideData + ++posIndex);
		float y = *(sideData + ++posIndex);
		float z = *(sideData + ++posIndex);
		float u = *(texCoord + ++texCoordIndex);
		float v = *(texCoord + ++texCoordIndex);

		glm::vec4 pos = glm::vec4(x, y, z, 1.0f);
		pos = model * pos; // after translating

		//Vertex vertex = { pos.x, pos.y, pos.z };

		this->verticles.push_back(pos.x);
		//cout << "x: " << this->verticles[++count];
		this->verticles.push_back(pos.y);
		//cout << " y: " << this->verticles[++count];
		this->verticles.push_back(pos.z);
		//cout << " z: " << this->verticles[++count];
		this->verticles.push_back(u);
		//cout << " u: " << this->verticles[++count];
		this->verticles.push_back(v);
		//cout << " v: " << this->verticles[++count];
		//cout << endl;
		
	}

	for (int i = 0; i < 6; i++) {
		this->indicates.push_back(*(indicate + i) + 4 * this->faceCount);
	}

	this->faceCount++;
}

void CubeRenderer::GenerateVBO()
{
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

const float* CubeRenderer::getCudeSide(Cube::CUBESIDE side)
{
	const float* sideData = NULL;

	switch (side)
	{
	case Cube::FRONT:
		sideData = Cube::FRONTSIDE;
		break;
	case Cube::BACK:
		sideData = Cube::BACKSIDE;
		break;
	case Cube::TOP:
		sideData = Cube::TOPSIDE;
		break;
	case Cube::BOTTOM:
		sideData = Cube::BOTTOMSIDE;
		break;
	case Cube::LEFT:
		sideData = Cube::LEFTSIDE;
		break;
	case Cube::RIGHT:
		sideData = Cube::RIGHTSIDE;
		break;
	default:
		sideData = NULL;
		break;
	}
	return sideData;
}

