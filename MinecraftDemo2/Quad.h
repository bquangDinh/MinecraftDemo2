#pragma once
#include "MathUtils.h"
#include "CubeUtils.h"

class Quad
{
public:
	Point p1, p2, p3, p4;
	int type;
	bool transparent;
	int direction;

	Quad(Point, Point, Point, Point, int, int, bool);
	Quad();

	bool equals(Quad);
};

