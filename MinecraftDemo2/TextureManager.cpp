#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture2D> TextureManager::Textures;
std::map<std::string, TextureCoord> TextureManager::TextureCoordPieceInAtlas;

Texture2D TextureManager::LoadTexture(const GLchar* file, GLboolean lapha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, false);
	return Textures[name];
}

Texture2D TextureManager::GetTexture(std::string name)
{
	return Textures[name];
}

void TextureManager::LoadTextureCoordAtlas(const char* file, int piecesInWidth, int piecesInHeight, std::string atlasName, TexturePiece pieces[], int countOfpieces)
{
	TextureManager::LoadTexture(file, false, atlasName);

	float baseOriPointX = 0.0f;
	float baseOriPointY = 0.0f;

	float widthOfpiece = 1.0f / (piecesInWidth + 1);
	float heightOfpiece = 1.0f / (piecesInHeight + 1);

	for (int i = 0; i < countOfpieces; i++) {
		float translateX = widthOfpiece * pieces[i].orderX;
		float translateY = heightOfpiece * pieces[i].orderY;

		float bottomLeftX = baseOriPointX + translateX;
		float bottomLeftY = baseOriPointY + translateY;

		TextureCoord texCoord = {
			bottomLeftX, bottomLeftY + heightOfpiece, // top left
			bottomLeftX + widthOfpiece, bottomLeftY + heightOfpiece, // top right
			bottomLeftX + widthOfpiece, bottomLeftY, // bottom right
			bottomLeftX, bottomLeftY // bottom left
		};

		printf("{ (%f,%f) (%f,%f) (%f,%f) (%f,%f) }\n", bottomLeftX, bottomLeftY + heightOfpiece, bottomLeftX + widthOfpiece, bottomLeftY + heightOfpiece, bottomLeftX + widthOfpiece, bottomLeftY, bottomLeftX, bottomLeftY);
		TextureCoordPieceInAtlas[pieces[i].name] = texCoord;
	}
}

TextureCoord TextureManager::GetTextureCoordInAtlas(std::string nameOfpiece)
{
	return TextureCoordPieceInAtlas[nameOfpiece];
}

void TextureManager::ClearTextures()
{
	for (auto iter : Textures) {
		glDeleteTextures(1, &iter.second.ID);
	}
}

Texture2D TextureManager::loadTextureFromFile(const GLchar* file, GLboolean alpha)
{
	Texture2D texture;

	int width, height, nrChannels;

	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	texture.Generate(width, height, data);

	stbi_image_free(data);

	return texture;
}
