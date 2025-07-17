#ifndef LOADER_H
#define LOADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../gfx/character.h"
#include <map>
#include "../gfx/shader.h"
#include "../gfx/texture.h"

namespace Loader
{
	std::string loadFile(const char *filePath);

	Shader loadShader(const char *vertexPath, const char *fragmentPath);

	Texture loadImage(const char *texturePath, GLint outputFormat, GLint sourceFormat, GLint wrap, GLint filter);

	std::map<char, Character> loadFont(const char *fontPath);
}
#endif
