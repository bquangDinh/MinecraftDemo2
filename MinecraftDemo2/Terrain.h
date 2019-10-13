#pragma once
#include <bitmap/bitmap_image.hpp>
#include "CubeChunk.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	void readHeightMap(const char* file);
};

