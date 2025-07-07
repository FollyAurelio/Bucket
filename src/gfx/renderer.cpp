#include "renderer.h"

Renderer::Renderer()
{
	vbo.buffer(rect_vertices, sizeof(rect_vertices));
	vao.attr(vbo, 0, 2, GL_FLOAT, 2*sizeof(float), 0);
	ebo.buffer(rect_indices, sizeof(rect_indices));
}

void Renderer::drawRectangle(
