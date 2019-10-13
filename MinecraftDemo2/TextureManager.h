#pragma once
#include <map>
#include <string>
#include "Texture2D.h"
#include "TextureCoord.h"

class TextureManager
{
public:
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, TextureCoord> TextureCoordPieceInAtlas;

	static Texture2D LoadTexture(const GLchar* file, GLboolean lapha, std::string name);

	static Texture2D GetTexture(std::string name);

	static void LoadTextureCoordAtlas(const char* file, int piecesInWidth, int piecesInHeight,std::string atlasName, TexturePiece pieces[], int countOfpieces);
	
	static TextureCoord GetTextureCoordInAtlas(std::string nameOfpiece);

	static void ClearTextures();

private:
	TextureManager() { }

	static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
};

