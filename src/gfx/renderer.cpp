#include "renderer.h"

Renderer::Renderer(float windowWidth, float windowHeight)
{	
	projection = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
		
}	

void Renderer::init()
{
	vbo.init();
	vao.init();
	ebo.init();
	rect_shader.init();
	vbo.buffer(rect_vertices, sizeof(rect_vertices));
	vao.attr(vbo, 0, 2, GL_FLOAT, 2*sizeof(float), 0);
	ebo.buffer(rect_indices, sizeof(rect_indices));
	//setting up camera and projection matrices
	camera = glm::mat4(1.0f);
	no_camera = glm::mat4(1.0f);

}

void Renderer::drawRectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed)
{
	rect_shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));
	rect_shader.setMatrix4("model", model);
	if (fixed)
	{
		rect_shader.setMatrix4("view", no_camera);
	}
	else
	{
		rect_shader.setMatrix4("view", camera);
	}
	rect_shader.setMatrix4("projection", projection);
	rect_shader.setVector3("color", color);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
