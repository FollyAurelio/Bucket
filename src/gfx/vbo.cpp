#include "vbo.h"

VBO::VBO(GLint t, bool d)
{
	type = t;
	dynamic = d;
	glGenBuffers(1, &handle);
}

void VBO::destroy()
{
	glDeleteBuffers(1, &handle);
}

void VBO::bind()
{
	glBindBuffer(type, handle);
}

void VBO::buffer(void *data, size_t size)
{
	bind();
	glBufferData(type, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
