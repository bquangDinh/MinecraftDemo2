#pragma once
#include "CubeRenderer.h"
#include "CubeUtils.h"
#include "TextureManager.h"
#include "Voxel.h"
#include "Quad.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeChunk
{
private:
	const float VOXEL_UNIT = 0.5f;

	Voxel Cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE] = { Voxel(false,AIR_BLOCK) };
	CubeRenderer cubeRenderer;

	bool hasChanged = false;

	glm::vec3 chunkPos;
	glm::mat4 model;

	CubeChunk* neighbors[6] = { NULL };

	//Voxel functions
	Voxel getVoxel(int, int, int);
	void setVoxel(int, int, int, int, bool);

	//meshing algorimn
	void stupid();

	void culling();
	bool isVisibleQuad(int x, int y, int z,int side);

	void greedy();
	void getQuad(int, int, int, int,Quad&);

public:
	bool hasCreated = false;

	CubeChunk();
	~CubeChunk();

	CubeChunk operator=(CubeChunk&);

	void Init(glm::vec3 position, int*, int, int);

	void CreateMesh(int*, int, int);

	void Generate();

	void AddNeighBor(CubeChunk*,int);
	CubeChunk* getNeighBor(int);

	void Update();
};

