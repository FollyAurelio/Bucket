#ifndef VAO_H
#define VAO_H
#include "gfx.h"
#include "vbo.h"

class VAO
{
public:
	GLuint handle;
	VAO();
	void bind();
	void destroy();
	void attr(VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
};

#endif
