#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include "gfx.h"

class Texture
{
public:
	unsigned int handle;
	Texture(const char* path, GLint outputFormat, GLint sourceFormat);
	void bind();
	void activate(GLint unit);
	void destory();
};
#endif
