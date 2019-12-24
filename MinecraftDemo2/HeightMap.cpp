#include "HeightMap.h"

std::vector<std::pair<float, VOXEL_TYPE>> HeightMap::map = {
	{0.1f, VOXEL_TYPE::ROCK} ,
	{0.5f, VOXEL_TYPE::DIRT} ,
	{0.1f, VOXEL_TYPE::GRASS},
	{0.3f, VOXEL_TYPE::ROCK}
};

float HeightMap::MOUNTAIN_THRESHOLD = 0.7f;