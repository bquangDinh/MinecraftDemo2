#pragma once



class Voxel
{
public:
	bool transparent;
	int type;

	Voxel();
	Voxel(bool, int);

	bool equals(Voxel);
};

