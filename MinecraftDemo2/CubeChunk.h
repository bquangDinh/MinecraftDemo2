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
#include <bitmap/bitmap_image.hpp>

class CubeChunk
{
private:
	const float VOXEL_UNIT = 1.0f;

	Voxel Cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE] = { Voxel(false,AIR_BLOCK) };
	const glm::vec3 Dimensions = glm::vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

	CubeRenderer cubeRenderer;

	bool hasChanged = false;

	glm::vec3 chunkPos;
	glm::mat4 model;

	CubeChunk* neighbors[6] = { NULL };

	//Voxel functions
	Voxel getVoxel(int, int, int);
	Voxel getVoxel(glm::vec3);
	void setVoxel(int, int, int, int, bool);

	//meshing algorimn
	void stupid();

	void culling();

	bool isVisibleQuad(int x, int y, int z,int side);

	bool compareStep(glm::vec3, glm::vec3, int, bool);
	bool IsBlockFaceVisible(glm::vec3, int, bool);
	Voxel setBlock(glm::vec3, int, bool);
	bool ContainsIndex(glm::vec3);
	int FlattenIndex(glm::vec3);
	void greedy();
	void getQuad(int, int, int, int,Quad&);

public:
	bool hasCreated = false;
	bool isReady = false;
	bool hasGenerated = false;

	CubeChunk();
	~CubeChunk();

	CubeChunk operator=(CubeChunk&);

	void Init(glm::vec3 position, int*, int, int);
	void Init(glm::vec3 position);

	void CreateMesh(int*, int, int);
	void CreateMesh();

	void Generate();
	void DoMeshing();

	void AddNeighBor(CubeChunk*,int);
	CubeChunk* getNeighBor(int);

	void Update();
};

