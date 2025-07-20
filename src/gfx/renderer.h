#ifndef RENDERER_H
#define RENDERER_H
#include "gfx.h"
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "texture.h"
#include "gmath.h"
#include "../data/loader.h"

#include <map>
#define BITMAP_WIDTH 18
#define BITMAP_HEIGHT 7
#define BITMAP_STEP (float)(1.0f / BITMAP_WIDTH)
#define BITMAP_DOWN (float)(1.0f / BITMAP_HEIGHT)

class Renderer
{
public:
	float rect_vertices[8] = {1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
				};
	unsigned int rect_indices[6] = {0,1,3,1,2,3};
	float vertices[16] = {0.0f, 0.0f, 0.0f, 0.0f,
			   1.0f, 0.0f, 1.0f, 0.0f,
			   0.0f,1.0f, 0.0f, 1.0f,
			   1.0f, 1.0f, 1.0f, 1.0f};
	unsigned int elements[6]= {0, 1, 2, 3, 1, 2};
	VBO glyph = VBO(GL_ARRAY_BUFFER, false);
	VBO eboglyph = VBO(GL_ELEMENT_ARRAY_BUFFER, false);
	VAO vaoglyph = VAO();
	Texture t = Loader::loadImage("res/fonts/charmap-oldschool_white.png", GL_RGBA, GL_RGB, GL_REPEAT, GL_LINEAR);
	Shader glyphS = Loader::loadShader("res/shaders/glyph.vs", "res/shaders/glyph.fs");
	Shader rect_shader = Loader::loadShader("res/shaders/basic.vs", "res/shaders/basic.fs");
	Shader text_shader = Loader::loadShader("res/shaders/text.vs", "res/shaders/text.fs");
	VBO rect_vbo = VBO(GL_ARRAY_BUFFER, false);
	VBO rect_ebo = VBO(GL_ELEMENT_ARRAY_BUFFER, false);
	VAO rect_vao = VAO();
	VBO text_vbo = VBO(GL_ARRAY_BUFFER, true);
	VAO text_vao = VAO();
	std::map <char, Character> characters;
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
	void drawText(std::string text, float x, float y, float scale, glm::vec3 color);
	void drawGlyph();
	

};

#endif
