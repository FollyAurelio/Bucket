#ifndef LOADER_H
#define LOADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "util.h"
#include "shader.h"

std::string loadFile(const char *filePath);
Shader loadShader(const char *vertexPath, const char *fragmentPath);
unsigned int loadImage(const char *texturePath, GLint outputFormat, GLint sourceFormat, GLint wrap, GLint filter);
std::map<char, Character> loadFont(const char *fontPath);
#endif
