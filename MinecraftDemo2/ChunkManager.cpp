#include "ChunkManager.h"

CubeChunk* ChunkManager::getChunk(int x, int z)
{
	return &this->Chunks[x + WORLD_CHUNK_COUNT * z];
}

CubeChunk* ChunkManager::setChunk(int x, int z)
{
	CubeChunk* chunk = this->getChunk(x, z);
	chunk->Init(glm::vec3(x * CHUNK_SIZE, 0, z * CHUNK_SIZE));
	return chunk;
}

void ChunkManager::AddNeighborsOfChunk(int x, int z)
{
	CubeChunk* chunk = this->getChunk(x, z);
	for (int side = 0; side < 4; side++) {
		if (side == FRONTSIDE) {
			if (z < WORLD_CHUNK_COUNT - 1) {
				if (this->getChunk(x, z + 1)->hasCreated == true) {
					chunk->AddNeighBor(this->getChunk(x, z + 1), side);
				}
			}
		}
		if (side == BACKSIDE) {
			if (z > 0) {
				if (this->getChunk(x, z - 1)->hasCreated == true) {
					chunk->AddNeighBor(this->getChunk(x, z - 1), side);
				}
			}
		}
		if (side == LEFTSIDE) {
			if (x > 0) {
				if (this->getChunk(x - 1, z)->hasCreated == true) {
					chunk->AddNeighBor(this->getChunk(x - 1, z), side);
				}
			}
		}
		if (side == RIGHTSIDE) {
			if (x < WORLD_CHUNK_COUNT - 1) {
				if (this->getChunk(x + 1, z)->hasCreated == true) {
					chunk->AddNeighBor(this->getChunk(x + 1, z), side);
				}
			}
		}
	}
}

void ChunkManager::GenerateHeightMap()
{
	for (int x = 0; x < WORLD_CHUNK_COUNT * CHUNK_SIZE; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT * CHUNK_SIZE; z++) {
			int height = rand() % 15 + 1;
			this->setHeightAt(x, z, height);
		}
	}
}

int ChunkManager::getHeightAt(int x, int z)
{
	return this->heightmap[x + WORLD_CHUNK_COUNT * CHUNK_SIZE * z];
}

void ChunkManager::setHeightAt(int x, int z, int height)
{
	this->heightmap[x + WORLD_CHUNK_COUNT * CHUNK_SIZE * z] = height;
}


ChunkManager::ChunkManager()
{
	srand(time(0));
}

void ChunkManager::Init()
{
	//this->GenerateHeightMap();

	for (int x = 0; x < WORLD_CHUNK_COUNT; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT; z++) {
			this->setChunk(x, z);
		}
	}

	cout << "NB process" << endl;

	for (int x = 0; x < WORLD_CHUNK_COUNT; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT; z++) {
			this->AddNeighborsOfChunk(x, z);
		}
	}

	cout << "Meshing..." << endl;

	for (int x = 0; x < WORLD_CHUNK_COUNT; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT; z++) {
			this->getChunk(x, z)->DoMeshing();
		}
	}

	cout << "Generating..." << endl;

	for (int x = 0; x < WORLD_CHUNK_COUNT; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT; z++) {
			this->getChunk(x, z)->Generate();
		}
	}
}

void ChunkManager::Update()
{
	for (int x = 0; x < WORLD_CHUNK_COUNT; x++) {
		for (int z = 0; z < WORLD_CHUNK_COUNT; z++) {
			this->getChunk(x, z)->Update();
		}
	}
}
