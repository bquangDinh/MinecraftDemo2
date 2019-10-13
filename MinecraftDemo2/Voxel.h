#pragma once

#define AIR_BLOCK 0
#define GRASS_BLOCK 1
#define ROCK_BLOCK 2

class Voxel
{
public:
	bool transparent;
	int type;

	Voxel();
	Voxel(bool, int);

	bool equals(Voxel);
};

