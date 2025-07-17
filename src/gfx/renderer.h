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
	VBO rect_vbo = VBO(GL_ARRAY_BUFFER, false);
	VBO rect_ebo = VBO(GL_ELEMENT_ARRAY_BUFFER, false);
	VAO rect_vao = VAO();
	VBO text_vbo = VBO(GL_ARRAY_BUFFER, true);
	//VBO text_vbo = VBO(GL_ARRAY_BUFFER, true);
	glm::vec2 cameraPosition = glm::vec2(0.0f, 0.0f);
	float cameraZoom = 1.0f;
	glm::mat4 camera;
	glm::mat4 inverseCamera;
	glm::mat4 no_camera;
	glm::mat4 projection;
	Renderer(float windowWidth, float windowHeight);
	void init();
	void setCamera();
	void drawRectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	void drawText();
	

};

#endif
