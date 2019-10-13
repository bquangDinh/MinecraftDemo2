#pragma once
#include <string>

typedef struct {
	float texCoord[8];
} TextureCoord;

typedef struct {
	std::string name;
	int orderX;
	int orderY;
} TexturePiece;