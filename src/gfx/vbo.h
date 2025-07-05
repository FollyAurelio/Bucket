#ifndef VBO_H
#define VBO_H
#include "gfx.h"

class VBO
{
public:
	GLuint handle;
	GLint type;
	bool dynamic;

	VBO(GLint type, bool dynamic);
	void destroy();
	void bind();
	void buffer(void *data, size_t size);
};

#endif

