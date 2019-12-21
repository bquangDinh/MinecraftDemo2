#pragma once
#include "Mathf.h"
#include <iostream>

class Color
{
private:
	const int MIN_COLOR = 0;
	const int MAX_COLOR = 255;
	const float MIN_COLOR_NORMALIZED = 0.0f;
	const float MAX_COLOR_NORMALIZED = 1.0f;

public:
	float red, green, blue, alpha;

	Color(int red, int green, int blue);
	Color(int red, int green, int blue, float alpha);
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);
	Color();
	~Color();
	Color operator=(const Color& c);
	Color operator=(Color& c);

	void printNormalizedColor();
	void printColor();
};

