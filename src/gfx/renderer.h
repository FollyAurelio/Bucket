#ifndef RENDERER_H
#define RENDERER_H
#include "gfx.h"
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "texture.h"
#include "gmath.h"
#include "../data/loader.h"

class Renderer
{
public:
	float rect_vertices[8] = {1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
				};
	unsigned int rect_indices[6] = {0,1,3,1,2,3};
	Shader rect_shader = Loader::loadShader("res/shaders/basic.vs", "res/shaders/basic.fs");
	VBO vbo = VBO(GL_ARRAY_BUFFER, false);
	VBO ebo = VBO(GL_ELEMENT_ARRAY_BUFFER, false);
	VAO vao = VAO();
	Renderer();
	void drawRectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color);
	void drawText();

};

#endif
