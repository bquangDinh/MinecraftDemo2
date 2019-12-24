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

Voxel::~Voxel()
{
}

Voxel& Voxel::operator=(const Voxel& v)
{
	transparent = v.transparent;
	type = v.type;
	return *this;
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
