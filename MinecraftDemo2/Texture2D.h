#pragma once
#include <glad/glad.h>

class Texture2D
{
public:
	//hold the ID of the texture
	GLuint ID;
	GLuint Internal_Format;
	GLuint Image_Format;
	GLuint Wrap_S, Wrap_T, Wrap_R;
	GLuint Filter_Min, Filter_Max;
	GLuint Width, Height;

	Texture2D();

	//Generates texture data from texture data
	void Generate(GLuint width,GLuint height,unsigned char* data);

	//bind texture to current state
	void Bind() const;	
};

