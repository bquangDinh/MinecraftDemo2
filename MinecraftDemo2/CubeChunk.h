#pragma once
#include "CubeRenderer.h"
#include "CubeUtils.h"
#include "TextureManager.h"
#include "Voxel.h"
#include <bitmap/bitmap_image.hpp>

class CubeChunk
{
private:
	Voxel Cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool CubeFaces[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * NUM_OF_SIDES];
	CubeRenderer cubeRenderer;

	Voxel getVoxel(int, int, int);
	void setVoxel(int, int, int, Voxel&);

	bool getVoxelFace(int, int, int, int);
	void setVoxelFace(int, int, int, int, bool);
	
	bool isVisibleSide(int, int, int, int);

	//meshing algorithm
	void stupid();
	void culling();
	void greedy();

public:
	CubeChunk();

	void Generate();

	void Update();
};

