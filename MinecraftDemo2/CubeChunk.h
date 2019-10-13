#pragma once
#include "CubeRenderer.h"
#include "CubeUtils.h"
#include "TextureManager.h"
#include <bitmap/bitmap_image.hpp>

class CubeChunk
{
private:
	CubeRenderer cubeRenderer;
	
	CubeData Cubes[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	bool mask[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE][6] = { false };

	CubeChunk *neighborChunks[6]; // 6 faces

	bool isVisibleSide(int, int, int, int);
	Cube::CUBESIDE getCubeSide(int);
	float* getTexCoord(CubeType, int);

public:
	CubeChunk();

	bool hasChanged = true;

	void AddBlock(int,int,int);
	void RemoveBlock();
	CubeType HasBlock(int,int,int);

	void GenerateTerrain(const char*);
	void Update();
};

