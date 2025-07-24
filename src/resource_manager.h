#ifndef LOADER_H
#define LOADER_H
#include "util.h"
#include "shader.h"

std::string loadFile(const char *filePath);
Shader loadShader(const char *vertexPath, const char *fragmentPath);
unsigned int loadImage(const char *texturePath, GLint outputFormat, GLint sourceFormat, GLint wrap, GLint filter);
Font loadFont(const char *fontPath);
#endif
