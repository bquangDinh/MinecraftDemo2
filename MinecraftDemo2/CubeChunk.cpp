#include "CubeChunk.h"

Voxel CubeChunk::getVoxel(int x, int y, int z)
{
	return this->Cubes[z + CHUNK_SIZE * (y + CHUNK_SIZE * x)];
}

void CubeChunk::setVoxel(int x, int y, int z, Voxel& cube)
{
	this->Cubes[z + CHUNK_SIZE * (y + CHUNK_SIZE * x)] = cube;
}

bool CubeChunk::getVoxelFace(int x, int y, int z, int side)
{
	return this->CubeFaces[side + NUM_OF_SIDES * (z + CHUNK_SIZE * (y + CHUNK_SIZE * x))];
}

void CubeChunk::setVoxelFace(int x, int y, int z, int side, bool value)
{
	this->CubeFaces[side + NUM_OF_SIDES * (z + CHUNK_SIZE * (y + CHUNK_SIZE * x))] = value;
}

bool CubeChunk::isVisibleSide(int x, int y, int z, int side)
{
	if (this->getVoxel(x, y, z).type == AIR_BLOCK) return false;

	if (side == FRONTSIDE) {
		if (z == CHUNK_SIZE - 1) {
			//at edge
			return true;
		}
		else {
			if (getVoxel(x, y, z + 1).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == BACKSIDE) {
		if (z == 0) {
			return true;
		}
		else {
			if (getVoxel(x, y, z - 1).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == LEFTSIDE) {
		if (x == 0) {
			return true;
		}
		else {
			if (getVoxel(x - 1, y, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == RIGHTSIDE) {
		if (x == CHUNK_SIZE - 1) {
			return true;
		}
		else {
			if (getVoxel(x + 1, y, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == TOPSIDE) {
		if (y == CHUNK_SIZE - 1) {
			return true;
		}
		else {
			if (getVoxel(x, y + 1, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == BOTTOMSIDE) {
		if (y == 0) {
			return true;
		}
		else {
			if (getVoxel(x, y - 1, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}

void CubeChunk::stupid()
{
	for (int side = 0; side < NUM_OF_SIDES; side++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					if (this->getVoxel(x, z, y).type != AIR_BLOCK) {
						this->setVoxelFace(x, z, y, side, true);
					}
				}
			}
		}
	}
}

void CubeChunk::culling()
{
	for (int side = 0; side < NUM_OF_SIDES; side++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					if (this->isVisibleSide(x, z, y, side) == true) {
						this->setVoxelFace(x, z, y, side, true);
					}
					else {
						this->setVoxelFace(x, z, y, side, false);
					}
				}
			}
		}
	}
}

void CubeChunk::greedy()
{

}

CubeChunk::CubeChunk()
{
	bitmap_image heightData("C:\\Users\\buiqu\\Downloads\\rsz_heightmap_2.bmp");

	if (!heightData) {
		cout << "Failed to read height map" << endl;
	}

	cout << "Width: " << heightData.width() << endl;
	cout << "Height: " << heightData.height() << endl;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			rgb_t colour;
			heightData.get_pixel(x, y, colour);
			double red = colour.red / 255.0f;
			int height = red * CHUNK_SIZE;
			if (height == 0) height = 1;
			for (int z = 0; z < CHUNK_SIZE; z++) {
				if (z <= height) {
					if (height >= GRASS_MIN_LIMIT && height <= GRASS_MAX_LIMIT) {
						Voxel cube(true, GRASS_BLOCK);
						this->setVoxel(x, z, y, cube);
					}
					else if (height >= ROCK_MIN_LIMIT && height <= ROCK_MAX_LIMIT) {
						Voxel cube(true, ROCK_BLOCK);
						this->setVoxel(x, z, y, cube);
					}
				}
				else {
					Voxel cube(true, AIR_BLOCK);
					this->setVoxel(x, z, y, cube);
				}
			}
		}
	}
}

void CubeChunk::Generate()
{
	this->culling();

	for (int side = 0; side < NUM_OF_SIDES; side++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					if (this->getVoxelFace(x, z, y, side) == true) {
						this->cubeRenderer.AddVerticleToVBO(side, glm::vec3(x, z, y), this->getVoxel(x, z, y).type);
					}
				}
			}
		}
	}

	this->cubeRenderer.GenerateVBO();
}

void CubeChunk::Update()
{
	this->cubeRenderer.Render();
}


