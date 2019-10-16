#include "CubeRenderer.h"
	
CubeRenderer::CubeRenderer()
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::AddVerticleToVBO(int side, glm::vec3 position, int type)
{
	//cout << "side: " << side << " type: " << type << endl;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	const float* sideData = this->getCudeSide(side);
	const float* texCoord = NULL;

	if (side == 0 || side == 1 || side == 2 || side == 3) {
		if (type == 1) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 4) {
		if (type == 1) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("grass_top").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == 5) {
		if (type == 1) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("grass_bottom").texCoord;
		}
		else if (type == 2) {
			//grass block
			texCoord = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}

	int posIndex = -1;
	int texCoordIndex = -1;

	const unsigned int* indicate = NULL;

	if (side == Cube::CUBESIDE::FRONT || side == Cube::CUBESIDE::TOP || side == Cube::CUBESIDE::LEFT) {
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

void CubeRenderer::AddQuadToVBO(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4,bool backface, int typeface, int side)
{
	//determine the indicates if that face is either backface or frontface
	if (backface == false) {
		//front face
		this->indicates.push_back(3 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(0 + 4 * this->faceCount);

		this->indicates.push_back(3 + 4 * this->faceCount);
		this->indicates.push_back(2 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
	}
	else {
		//back face
		this->indicates.push_back(0 + 4 * this->faceCount);
		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(3 + 4 * this->faceCount);

		this->indicates.push_back(1 + 4 * this->faceCount);
		this->indicates.push_back(2 + 4 * this->faceCount);
		this->indicates.push_back(3 + 4 * this->faceCount);
	}

	//determine the texure coord
	const float* texCoord = this->getCubeTexCoord(side, typeface);

	this->verticles.push_back(p1.x);
	this->verticles.push_back(p1.y);
	this->verticles.push_back(p1.z);

	this->verticles.push_back(*(texCoord + 0));
	this->verticles.push_back(*(texCoord + 0));

	this->verticles.push_back(p2.x);
	this->verticles.push_back(p2.y);
	this->verticles.push_back(p2.z);

	this->verticles.push_back(*(texCoord + 1));
	this->verticles.push_back(*(texCoord + 1));

	this->verticles.push_back(p3.x);
	this->verticles.push_back(p3.y);
	this->verticles.push_back(p3.z);

	this->verticles.push_back(*(texCoord + 2));
	this->verticles.push_back(*(texCoord + 2));

	this->verticles.push_back(p4.x);
	this->verticles.push_back(p4.y);
	this->verticles.push_back(p4.z);

	this->verticles.push_back(*(texCoord + 3));
	this->verticles.push_back(*(texCoord + 3));

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

const float* CubeRenderer::getCudeSide(int side)
{
	const float* sideData = NULL;

	switch (side)
	{
	case 0:
		sideData = Cube::FRONTSIDE;
		break;
	case 1:
		sideData = Cube::BACKSIDE;
		break;
	case 4:
		sideData = Cube::TOPSIDE;
		break;
	case 5:
		sideData = Cube::BOTTOMSIDE;
		break;
	case 2:
		sideData = Cube::LEFTSIDE;
		break;
	case 3:
		sideData = Cube::RIGHTSIDE;
		break;
	default:
		sideData = NULL;
		break;
	}
	return sideData;
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

