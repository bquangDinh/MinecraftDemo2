#pragma once
#include "GLM.h"
#include "CubeChunk.h"
#include <ctime>
#include <cstdlib>
#include <unordered_map>

class ChunkManager
{
private:
	std::unordered_map<int, CubeChunk> map;
	glm::vec3 Dimensions, ChunkDimensions;
	bool hasInitialized;

	int FlattenIndex(glm::vec3 pos);
	bool isContainsIndex(glm::vec3 pos);
	int getActualSide(int direction, bool backface);

public:
	CubeChunk* getChunk(glm::vec3 pos);
	CubeChunk* getChunk(glm::vec3 pos, int direction, bool backface);
	void setChunk(glm::vec3 pos);

	ChunkManager(glm::vec3 dimensions, glm::vec3 chunkDimensions);
	ChunkManager();
	~ChunkManager();

	void Initialize();
	void Update();
};

