#pragma once
#include <glad/glad.h>
#include <algorithm>
#include <vector>

class Texture2DArray
{
public:
	GLuint ID;
	GLuint Internal_Format;
	GLuint Image_Format;
	GLuint Wrap_S, Wrap_T, Wrap_R;
	GLuint Filter_Min, Filter_Max;
	GLuint Width, Height;

	Texture2DArray();

	void Generate(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;
};

