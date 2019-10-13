#include "CubeChunk.h"

bool CubeChunk::isVisibleSide(int x, int y, int z, int side)
{
	if (this->Cubes[x][y][z].cubeType.type == AIR_BLOCK) return false;

	switch (side)
	{
	case FRONTSIDE:
		if (z == CHUNK_SIZE - 1) {
			return true;
		}
		else {
			if (this->Cubes[x][y][z - 1].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		return false;
	case BACKSIDE:
		if (z == 0) {
			return true;
		}
		else {
			if (this->Cubes[x][y][z + 1].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		return false;
	case LEFTSIDE:
		if (x == 0) {
			return true;
		}
		else {
			if (this->Cubes[x - 1][y][z].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		break;
	case RIGHTSIDE:
		if (x == 300 - 1) {
			return true;
		}
		else {
			if (this->Cubes[x + 1][y][z].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		return false;
	case TOPSIDE:
		if (y == 144 - 1) {
			return true;
		}
		else {
			if (this->Cubes[x][y + 1][z].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		return false;
	case BOTTOMSIDE:
		if (y == 0) {
			return true;
		}
		else {
			if (this->Cubes[x][y - 1][z].cubeType.type == AIR_BLOCK) {
				return true;
			}
		}
		return false;
	}
	return false;
}

Cube::CUBESIDE CubeChunk::getCubeSide(int side)
{
	Cube::CUBESIDE cSide;
	switch (side)
	{
	case FRONTSIDE:
		cSide = Cube::CUBESIDE::FRONT;
		break;
	case BACKSIDE:
		cSide = Cube::CUBESIDE::BACK;
		break;
	case LEFTSIDE:
		cSide = Cube::CUBESIDE::LEFT;
		break;
	case RIGHTSIDE:
		cSide = Cube::CUBESIDE::RIGHT;
		break;
	case TOPSIDE:
		cSide = Cube::CUBESIDE::TOP;
		break;
	case BOTTOMSIDE:
		cSide = Cube::CUBESIDE::BOTTOM;
		break;
	}
	return cSide;
}

float* CubeChunk::getTexCoord(CubeType ctype,int side)
{
	float* texPointer = NULL;

	if (side == FRONTSIDE || side == BACKSIDE || side == LEFTSIDE || side == RIGHTSIDE) {
		if (ctype.type == GRASS_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("grass_side").texCoord;
		}
		if (ctype.type == ROCK_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else if (side == TOPSIDE) {
		if (ctype.type == GRASS_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("grass_top").texCoord;
		}
		if (ctype.type == ROCK_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}
	else {
		if (ctype.type == GRASS_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("grass_bottom").texCoord;
		}
		if (ctype.type == ROCK_BLOCK) {
			texPointer = TextureManager::GetTextureCoordInAtlas("rock").texCoord;
		}
	}

	return texPointer;
}

CubeChunk::CubeChunk()
{
	
}

void CubeChunk::AddBlock(int x, int y, int z)
{
}

CubeType CubeChunk::HasBlock(int x, int y, int z)
{
	return CubeType();
}

void CubeChunk::GenerateTerrain(const char* heightmap)
{
	cout << "Reading Height Map..." << endl;

	bitmap_image heightData(heightmap);

	if (!heightData) {
		cout << "Failed to load height map" << endl;
		return;
	}

	const unsigned int imgWidth = heightData.width();
	const unsigned int imgHeight = heightData.height();

	cout << "Height: " << imgHeight << " Width: " << imgWidth << endl;

	cout << "Generating Terrain..." << endl;

	for (int x = 0; x < imgWidth; x++) {
		for (int y = 0; y < imgHeight; y++) {

			rgb_t colour;
			heightData.get_pixel(x, y, colour);
			float r = colour.red;
			r /= 255.0f;
			int height = r * 15;
			//cout << height << endl;
			for (int z = 0; z < CHUNK_SIZE; z++) {
				if (z > height || height == 0) {
					CubeType cubeType = { AIR_BLOCK };
					Location cubeLocation = { x, y, z };
					CubeData cubeData = { cubeLocation, cubeType };
					this->Cubes[x][y][z] = cubeData;
				}
				else {
					CubeType cubeType = { GRASS_BLOCK };
					Location cubeLocation = { x, y, z };
					CubeData cubeData = { cubeLocation, cubeType };
					this->Cubes[x][y][z] = cubeData;
				}			
			}
		}
	}

	for (int x = 0; x < imgWidth; x++) {
		for (int y = 0; y < imgHeight; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int side = 0; side < 6; side++) {
					if (this->isVisibleSide(x, y, z, side) == true) {
						this->cubeRenderer.AddVerticleToVBO(this->getCubeSide(side), glm::vec3(x, y, z), this->getTexCoord(this->Cubes[x][y][z].cubeType, side));
					}
				}
			}
		}
	}

	

	this->cubeRenderer.GenerateVBO();
	cout << "Done" << endl;
}

void CubeChunk::Update()
{
	this->cubeRenderer.Render();
}
