#include "Quad.h"

Quad::Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, int type, int face, bool transparent)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->type = type;
	this->face = face;
	this->transparent = transparent;
}

Quad::Quad()
{
	this->p1 = glm::vec3();
	this->p2 = glm::vec3();
	this->p3 = glm::vec3();
	this->p4 = glm::vec3();
	this->type = AIR_BLOCK;
	this->face = SIDE::FRONT;
	this->transparent = true;
}

bool Quad::equals(Quad another)
{
	if (this->type == another.type && this->transparent == another.transparent) return true;
	return false;
}

int Quad::getType()
{
	return this->type;
}

int Quad::getFace()
{
	return this->face;
}

bool Quad::isTransparent()
{
	return this->transparent;
}

void Quad::RotateQuadOrder90()
{
	glm::vec3 t1, t2, t3;
	t1 = p1;
	t2 = p2;
	t3 = p3;

	p1 = p4;
	p2 = t1;
	p3 = t2;
	p4 = t3;
}

void Quad::RotateQuadOrder90Counter()
{
	glm::vec3 t1;
	t1 = p1;
	p1 = p2;
	p2 = p3;
	p3 = p4;
	p4 = t1;
}

void Quad::RolateQuadOrder90(glm::vec4& p1, glm::vec4& p2, glm::vec4& p3, glm::vec4& p4)
{
	glm::vec4 t1, t2, t3;
	t1 = p1;
	t2 = p2;
	t3 = p3;

	p1 = p4;
	p2 = t1;
	p3 = t2;
	p4 = t3;
}

void Quad::RolateQuadOrder90Counter(glm::vec4& p1, glm::vec4& p2, glm::vec4& p3, glm::vec4& p4)
{
	glm::vec4 t1;
	t1 = p1;
	p1 = p2;
	p2 = p3;
	p3 = p4;
	p4 = t1;
}
