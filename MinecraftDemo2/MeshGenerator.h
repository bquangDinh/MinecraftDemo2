#pragma once
#include "GLM.h"
#include "Voxel.h"
#include <vector>
#include <math.h>  
#include <PerlinNoise.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include "HeightMap.h"

enum TERRAIN_GENERATION_METHOD {
	SIMPLEX,
	PERLIN
};

enum MESH_SHAPE {
	CUBE,
	SPHERE
};

class MeshGenerator
{
public:
	static void GenerateTerrain(glm::vec3 dimensions, std::vector<Voxel>& voxels, TERRAIN_GENERATION_METHOD method);
	static void GenerateShape(glm::vec3 dimensions, std::vector<Voxel>& voxels, MESH_SHAPE shape);
private:
	//test
	//used for continious terrain
	static int X, Y, Z;

	static void ShapeGenerator(glm::vec3 lrange, glm::vec3 rrange, std::vector<Voxel>& voxels, bool (*checkingFunc)(glm::vec3, glm::vec3));
	static void TerrainGenerator(glm::vec3 lrange, glm::vec3 rrange, std::vector<Voxel>& voxels, bool(*checkingFunc)(glm::vec3, glm::vec3, siv::PerlinNoise noise, float& height));
	static bool sphereF(glm::vec3 pos, glm::vec3 dimensions);
	static bool cubeF(glm::vec3 pos, glm::vec3 dimensions);
	static bool perlinNoiseF(glm::vec3 pos, glm::vec3 dimensions, siv::PerlinNoise noise);
	static bool perlinNoise3DF(glm::vec3 pos, glm::vec3 dimensions, siv::PerlinNoise noise, float& height);

	static VOXEL_TYPE determineTextureByHeight(int index, int height, int max_height);

	MeshGenerator() {};
	~MeshGenerator();
};

