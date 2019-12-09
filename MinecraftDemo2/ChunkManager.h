#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeChunk.h"
#include <ctime>
#include <cstdlib>

#define WORLD_WIDTH 2 // 10 chunks
#define WORLD_CHUNK_COUNT 1

class ChunkManager
{
private:
	CubeChunk* getChunk(int x, int z);
	CubeChunk* setChunk(int x, int z);
	void AddNeighborsOfChunk(int x, int z);
	CubeChunk Chunks[WORLD_CHUNK_COUNT * WORLD_CHUNK_COUNT];
	int heightmap[WORLD_CHUNK_COUNT * CHUNK_SIZE * WORLD_CHUNK_COUNT * CHUNK_SIZE] = { 1 };

	void GenerateHeightMap();

	int getHeightAt(int x, int z);
	void setHeightAt(int x, int z, int height);
public:

	ChunkManager();

	void Init();
	void Update();
};

