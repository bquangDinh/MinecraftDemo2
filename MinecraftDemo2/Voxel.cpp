#include "Voxel.h"

Voxel::Voxel()
{
	this->transparent = true;
	this->type = VOXEL_TYPE::AIR;
}

Voxel::Voxel(bool transparent, int type)
{
	this->transparent = transparent;
	this->type = type;
}

bool Voxel::equals(Voxel another)
{
	if (this->transparent == another.transparent && this->type == another.type) return true;
	return false;
}

bool Voxel::isSolid()
{
	return this->type != VOXEL_TYPE::AIR;
}
