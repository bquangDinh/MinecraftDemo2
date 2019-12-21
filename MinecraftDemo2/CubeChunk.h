#pragma once
#include "MeshBuilder.h"
#include "CubeUtils.h"
#include "GLM.h"
#include "TextureManager.h"
#include "Voxel.h"
#include "Quad.h"
#include <vector>
#include "MeshGenerator.h"

enum MESHING_METHOD {
	STUPID,
	CULLING,
	GREEDY
};

class CubeChunk
{
private:
	const float VOXEL_UNIT;
	std::vector<Voxel> voxels;
	glm::vec3 Dimensions, ChunkPosition;
	glm::mat4 model;
	MeshBuilder meshBuider;
	CubeChunk* neighbors[6] = { nullptr };

	void setDimensions(int x,int y,int z);
	void setDimensions(glm::vec3 dimensions);

	int FlattenIndex(glm::vec3 pos);
	
	bool isContainsPosition(glm::vec3 pos);
	bool isBlockFaceVisible(glm::vec3 pos, int direction, bool backface);
	bool compareStep(glm::vec3 pos1, glm::vec3 pos2, int direction, bool backface);
	int getActualFace(int direction, bool backface);

	//meshing algorthrimn
	void stupid();
	void culling();
	void greedy();

	Voxel getVoxelNeighbor(glm::vec3 pos, int direction, bool backface);
public: 
	bool hasChanged;
	bool hasGeneratedTerrain;

	CubeChunk(glm::vec3 pos, glm::vec3 dimensions);
	CubeChunk();
	~CubeChunk();

	Voxel getVoxel(int x, int y, int z);
	Voxel getVoxel(glm::vec3 pos);

	void AddNeighbor(CubeChunk* chunk, SIDE side);
	CubeChunk* getNeighbor(SIDE side);
	bool hasNeighbor(SIDE side);

	void DoMeshing(MESHING_METHOD meshing_method);
	void GenerateTerrain();
	void Update();
};

