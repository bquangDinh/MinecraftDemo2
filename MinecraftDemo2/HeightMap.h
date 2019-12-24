#pragma once
#include <map>
#include "CubeUtils.h"
#include <vector>

class HeightMap
{
public:
	static std::vector<std::pair<float, VOXEL_TYPE>> map;
	static float MOUNTAIN_THRESHOLD;
};

