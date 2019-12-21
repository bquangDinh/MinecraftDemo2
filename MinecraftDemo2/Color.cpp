#include "Color.h"

Color::Color(int red, int green, int blue)
{
	this->red = Mathf::Clamp(red, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->green = Mathf::Clamp(green, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->blue = Mathf::Clamp(blue, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->alpha = 1.0f;
}

Color::Color(int red, int green, int blue, float alpha)
{
	this->red = Mathf::Clamp(red, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->green = Mathf::Clamp(green, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->blue = Mathf::Clamp(blue, MIN_COLOR, MAX_COLOR) / 255.0f;
	this->alpha = Mathf::Clamp(alpha, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
}

Color::Color(float red, float green, float blue)
{
	this->red = Mathf::Clamp(red, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->green = Mathf::Clamp(green, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->blue = Mathf::Clamp(blue, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->alpha = 1.0f;
}

Color::Color(float red, float green, float blue, float alpha)
{
	this->red = Mathf::Clamp(red, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->green = Mathf::Clamp(green, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->blue = Mathf::Clamp(blue, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
	this->alpha = Mathf::Clamp(alpha, MIN_COLOR_NORMALIZED, MAX_COLOR_NORMALIZED);
}

Color::Color()
{
	this->red = 0.5f;
	this->green = 0.5f;
	this->blue = 0.5f;
	this->alpha = 1.0f;
}

Color::~Color()
{
}

Color Color::operator=(Color& c)
{
	Color clr(c.red, c.green, c.blue, c.alpha);
	return clr;
}

void Color::printNormalizedColor()
{
	std::cout << "R:" << this->red << " |G: " << this->green << " |B: " << this->blue << std::endl;
}

void Color::printColor()
{
	std::cout << "R: " << this->red * 255.0f << " |G: " << this->green * 255.0f << " |B: " << this->blue * 255.0f << std::endl;
}
