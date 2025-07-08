#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include "gfx.h"

class Texture
{
public:
	unsigned int handle;
	Texture(unsigned char *data, GLint outputFormat, int width, int height, GLint sourceFormat, GLint wrap, GLint filter);
	void bind();
	void activate(GLint unit);
	void destory();
};
#endif
