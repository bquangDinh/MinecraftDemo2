#pragma once

#include "CubeUtils.h"

class Voxel
{
public:
	bool transparent;
	int type;

	Voxel();
	Voxel(bool, int);

	bool equals(Voxel);
};

