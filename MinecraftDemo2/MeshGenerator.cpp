#include "MeshGenerator.h"

void MeshGenerator::GenerateTerrain(glm::vec3 dimensions, std::vector<Voxel>& voxels, TERRAIN_GENERATION_METHOD method)
{
	if (method == TERRAIN_GENERATION_METHOD::PERLIN) {
		TerrainGenerator(glm::vec3(0, 0, 0), dimensions, voxels, &perlinNoiseF);
	}
}

void MeshGenerator::GenerateShape(glm::vec3 dimensions, std::vector<Voxel>& voxels, MESH_SHAPE shape)
{
	if (shape == MESH_SHAPE::CUBE) {
		ShapeGenerator(glm::vec3(0, 0, 0), dimensions, voxels, &cubeF);
	}

	if (shape == MESH_SHAPE::SPHERE) {
		ShapeGenerator(glm::vec3(0, 0, 0), dimensions, voxels, &sphereF);
	}
}

void MeshGenerator::ShapeGenerator(glm::vec3 lrange, glm::vec3 rrange, std::vector<Voxel>& voxels, bool(*checkingFunc)(glm::vec3, glm::vec3))
{
	glm::vec3 dimensions = glm::vec3(rrange.x - lrange.x, rrange.y - lrange.y, rrange.z - lrange.z);
	int x, y, z;

	for (x = lrange.x; x < rrange.x; ++x) {
		for (y = lrange.y; y < rrange.y; ++y) {
			for (z = lrange.z; z < rrange.z; z++) {
				if (checkingFunc(glm::vec3(x, y, z), dimensions)) {
					Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::GRASS);
					voxels.push_back(v);
				}
				else {
					Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
					voxels.push_back(v);
				}
			}
		}
	}
}

void MeshGenerator::TerrainGenerator(glm::vec3 lrange, glm::vec3 rrange, std::vector<Voxel>& voxels, bool(*checkingFunc)(glm::vec3, glm::vec3, siv::PerlinNoise noise))
{
	glm::vec3 dimensions = glm::vec3(rrange.x - lrange.x, rrange.y - lrange.y, rrange.z - lrange.z);
	int x, y, z;
	
	uint32_t seed = rand() % (19999 - 10000 + 1) + 10000;
	siv::PerlinNoise noise(seed);

	for (x = lrange.x; x < rrange.x; ++x) {
		for (y = lrange.y; y < rrange.y; ++y) {
			for (z = lrange.z; z < rrange.z; z++) {
				if (checkingFunc(glm::vec3(x, y, z), dimensions, noise)) {
					Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::GRASS);
					voxels.push_back(v);
				}
				else {
					Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
					voxels.push_back(v);
				}
			}
		}
	}
}

bool MeshGenerator::sphereF(glm::vec3 pos, glm::vec3 dimensions)
{
	if (dimensions.x != dimensions.y || dimensions.x != dimensions.z || dimensions.y != dimensions.z)
	{
#ifdef DEBUG
		printf("The sphere must have the unique radius !\n");
#endif // DEBUG	
		return false;
	}

	return (pow(pos.x - (dimensions.x / 2), 2) + pow(pos.y - (dimensions.y / 2), 2) + pow(pos.z - (dimensions.z / 2), 2)) <= pow(dimensions.x / 2, 2);
}

bool MeshGenerator::cubeF(glm::vec3 pos, glm::vec3 dimensions)
{
	//nothing to check here
	return true;
}

bool MeshGenerator::perlinNoiseF(glm::vec3 pos, glm::vec3 dimensions, siv::PerlinNoise noise)
{
	return pos.y <= abs(noise.octaveNoise0_1(pos.x / 10, pos.z / 10, 8)) * dimensions.y;
}

MeshGenerator::~MeshGenerator()
{
}

