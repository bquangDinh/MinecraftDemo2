#include "Texture2DArray.h"

Texture2DArray::Texture2DArray() : Internal_Format(GL_RGBA8), Image_Format(GL_RGBA), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Wrap_R(GL_REPEAT), Filter_Min(GL_NEAREST), Filter_Max(GL_NEAREST), Width(0), Height(0)
{
	glGenTextures(1, &this->ID);
}

void Texture2DArray::Generate(GLuint width, GLuint height, unsigned char* data)
{
	this->Width = width;
	this->Height = height;
	int tileW = width / 16;
	int tileH = height / 16;

	printf("tileW: %d\ntileH: %d\n", tileW, tileH);

	int channels = 4;

	int tilesX = 16;
	int tilesY = 16;
	int imageCount = tilesX * tilesY;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
	
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, this->Internal_Format, tileW, tileH, imageCount, 0, this->Image_Format, GL_UNSIGNED_BYTE, nullptr);

	std::vector<unsigned char> tile(tileW * tileH * channels);
	int tileSizeX = tileW * channels;
	int rowLen = tilesX * tileSizeX;

	for (int iy = 0; iy < tilesY; ++iy) {
		for (int ix = 0; ix < tilesX; ++ix) {
			unsigned char* ptr = data + iy * rowLen + ix * tileSizeX;
			for (int row = 0; row < tileH; ++row) {
				std::copy(ptr + row * rowLen, ptr + row * rowLen + tileSizeX, tile.begin() + row * tileSizeX);
			}

			int i = iy * tilesX + ix;
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tileW, tileH, 1, this->Image_Format, GL_UNSIGNED_BYTE, tile.data());
		}
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, this->Wrap_R);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Texture2DArray::Bind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
}
