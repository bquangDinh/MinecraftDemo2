#pragma once
#include "MathUtils.h"
#include "CubeUtils.h"
#include <glm/glm.hpp>

class Quad
{
private:
	int type;
	bool transparent;
	int face;
public:
	glm::vec3 p1, p2, p3, p4;

	Quad(glm::vec3, glm::vec3, glm::vec3, glm::vec3, int, int, bool);
	Quad();

	bool equals(Quad);
	int getType();
	int getFace();
	bool isTransparent();

	static void RolateQuadOrder90(glm::vec4&, glm::vec4&, glm::vec4&, glm::vec4&);
	static void RolateQuadOrder90Counter(glm::vec4&, glm::vec4&, glm::vec4&, glm::vec4&);
};

