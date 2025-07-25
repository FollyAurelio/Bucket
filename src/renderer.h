#ifndef RENDERER_H
#define RENDERER_H
#include "util.h"
#include "shader.h"
#include "resource_manager.h"
#include "piece_table.h"



class Renderer
{
public:
	float rect_vertices[8] = {1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
				};
	unsigned int rect_indices[6] = {0,1,3,1,2,3};
	Shader rect_shader = loadShader("res/shaders/basic.vs", "res/shaders/basic.fs");
	Shader text_shader = loadShader("res/shaders/text.vs", "res/shaders/text.fs");
	unsigned int rect_vbo;
	unsigned int rect_ebo;
	unsigned int rect_vao;
	unsigned int text_vbo; 
	unsigned int text_vao;
	Font font;
	glm::vec2 cameraPosition = glm::vec2(0.0f, 0.0f);
	float cameraZoom = 1.0f;
	glm::mat4 camera;
	glm::mat4 inverseCamera;
	glm::mat4 no_camera;
	glm::mat4 projection;
	Renderer(float windowWidth, float windowHeight);
	void init();
	void setCamera();
	void drawRectangle(Shader shader, glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	void drawText(Shader shader, std::string text, glm::vec2 position, float scale, glm::vec4 color, bool fixed);
	void drawEditorText(Shader shader, PieceTable *sequence, glm::vec2 position, float scale, glm::vec4 color, bool fixed);
	

};

#endif
