#include "MeshGenerator.h"

int MeshGenerator::X(0);
int MeshGenerator::Y(0);
int MeshGenerator::Z(0);

void MeshGenerator::GenerateTerrain(glm::vec3 dimensions, std::vector<Voxel>& voxels, TERRAIN_GENERATION_METHOD method)
{
	if (method == TERRAIN_GENERATION_METHOD::PERLIN) {
		TerrainGenerator(glm::vec3(0, 0, 0), dimensions, voxels, &perlinNoise3DF);
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

void MeshGenerator::TerrainGenerator(glm::vec3 lrange, glm::vec3 rrange, std::vector<Voxel>& voxels, bool(*checkingFunc)(glm::vec3, glm::vec3, siv::PerlinNoise noise, float& height))
{
	glm::vec3 dimensions = glm::vec3(rrange.x - lrange.x, rrange.y - lrange.y, rrange.z - lrange.z);
	int x, y, z, heightOffsetX, heightOffsetZ;
	float height;

	uint32_t seed = rand() % (19999 - 10000 + 1) + 10000;
	siv::PerlinNoise noise(seed);

	for (x = lrange.x; x < rrange.x; ++x) {
		for (y = lrange.y; y < rrange.y; ++y) {
			for (z = lrange.z; z < rrange.z; z++) {
				if (y == 0) {
					Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::ROCK);
					voxels.push_back(v);
					continue;
				}
				if (checkingFunc(glm::vec3(x,y,z),dimensions,noise, height)) {
					if ((int)height == 1) height += 1;
					heightOffsetX = rand() % ((int)height - 1) + 1;
					heightOffsetZ = rand() % ((int)height - 1) + 1;
					if (y <= 5 || (x == lrange.x && y < height - heightOffsetX) || (x == rrange.x - 1 && y < height - heightOffsetX) || (z == lrange.z && y < height - heightOffsetZ) || (z == rrange.z - 1 && y < height - heightOffsetZ)) {
						Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::ROCK);
						voxels.push_back(v);
						continue;
					}
					if (y >= height - 1) {
						Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::GRASS);
						voxels.push_back(v);
					}
					else {
						Voxel v(VOXEL_TRANSPARENT::FALSE, VOXEL_TYPE::DIRT);
						voxels.push_back(v);
					}				
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
	return pos.y <= abs(noise.octaveNoise0_1(pos.x / 15, pos.z / 15, 2)) * dimensions.y;
}

bool MeshGenerator::perlinNoise3DF(glm::vec3 pos, glm::vec3 dimensions, siv::PerlinNoise noise, float& height)
{
	float terrainHeight = abs(noise.octaveNoise0_1(pos.x / 15, pos.z / 15, 2)) * dimensions.y;
	height = terrainHeight;
	float perlin3D = noise.octaveNoise0_1(pos.x / 15, pos.y / 15, pos.z / 15, 2);
	float threshold = 0.6f;
	return (pos.y <= terrainHeight) && (perlin3D <= threshold);
}

VOXEL_TYPE MeshGenerator::determineTextureByHeight(int index, int height, int max_height)
{
	float scale = (float)height / (float)max_height;
	float indexScale = (float)index / (float)height;

	if (scale < HeightMap::MOUNTAIN_THRESHOLD) {
		if (index == height) {
			//make grass is the top layer
			return VOXEL_TYPE::GRASS;
		}
		else {
			float curr = 0.0f;
			for (int i = 0; i < HeightMap::map.size(); ++i) {
				printf("%d\n", i);
				if (indexScale <= HeightMap::map[i].first + curr) {
					return HeightMap::map[i].second;
				}
				curr += HeightMap::map[i].first;
			}
		}
	}
	else {
		float curr = 0.0f;
		for (int i = 0; i < HeightMap::map.size(); ++i) {
			if (indexScale <= HeightMap::map[i].first + curr) {
				return HeightMap::map[i].second;
			}
			curr += HeightMap::map[i].first;
		}
	}

	return VOXEL_TYPE::GRASS;
}

MeshGenerator::~MeshGenerator()
{
}

