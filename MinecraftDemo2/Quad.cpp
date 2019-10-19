#include "Quad.h"

Quad::Quad(Point p1, Point p2, Point p3, Point p4, int type, int direction, bool transparent)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->type = type;
	this->transparent = transparent;
	this->direction = direction;
}

Quad::Quad()
{
	this->p1 = { 0,0,0 };
	this->p2 = { 0,0,0 };
	this->p3 = { 0,0,0 };
	this->p4 = { 0,0,0 };
	this->type = AIR_BLOCK;
	this->direction = FRONTSIDE;
	this->transparent = true;
}

bool Quad::equals(Quad another)
{
	if (this->type == another.type && this->transparent == another.transparent) return true;
	return false;
}
