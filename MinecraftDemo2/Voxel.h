#pragma once

#include "CubeUtils.h"

class Voxel
{
public:
	bool transparent;
	int type;

	Voxel();
	Voxel(bool, int);
	~Voxel();

	//copy-constructor
	Voxel& operator=(const Voxel& v);

	bool equals(Voxel);
	bool isSolid();
};

