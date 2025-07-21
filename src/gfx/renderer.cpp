#include "renderer.h"

Renderer::Renderer(float windowWidth, float windowHeight)
{	
	projection = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
		
}	

void Renderer::init()
{
	rect_vbo.init();
	rect_vao.init();
	rect_ebo.init();
	rect_shader.init();
	rect_vbo.buffer(rect_vertices, sizeof(rect_vertices));
	rect_vao.attr(rect_vbo, 0, 2, GL_FLOAT, 2*sizeof(float), 0);
	rect_ebo.buffer(rect_indices, sizeof(rect_indices));

	text_vbo.init();
	text_vao.init();
	text_vao.bind();
	text_shader.init();
	text_vbo.buffer(NULL, sizeof(float) * 6 * 4);
	text_vao.attr(text_vbo, 0, 4, GL_FLOAT, 4*sizeof(float), 0);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelStorei(GL_PACK_ALIGNMENT, 1);
	characters = Loader::loadFont("res/fonts/times.ttf");

	glyph.init();
	vaoglyph.init();
	eboglyph.init();
	glyphS.init();
	t.init();
	glyph.buffer(vertices, sizeof(vertices));
	vaoglyph.attr(glyph, 0, 4, GL_FLOAT, 4*sizeof(float), 0);
	eboglyph.buffer(elements, sizeof(elements));


	for(unsigned char c = 0; c < 128; c++)
	{
		characters[c].texture.init();
	}
	camera = glm::mat4(1.0f);
	inverseCamera = glm::mat4(1.0f);
	no_camera = glm::mat4(1.0f);
}

void Renderer::setCamera()
{
	camera = glm::mat4(1.0f);
	camera = glm::translate(camera, glm::vec3(cameraPosition.x * 100.0f, cameraPosition.y * 100.0f, 0.0f));
	camera = glm::scale(camera, glm::vec3(cameraZoom, cameraZoom, 1.0f));
	inverseCamera = glm::inverse(camera);
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
	rect_vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::drawText(std::string text, float x, float y, float scale, glm::vec3 color)
{
// activate corresponding render state
	text_shader.use();
	text_shader.setInt("text", 0);
	text_shader.setVector3("textColor", color);
	text_shader.setMatrix4("view", camera);
	text_shader.setMatrix4("projection", projection);
	glActiveTexture(GL_TEXTURE0);
	text_vao.bind();
	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		//std::cout << (char)*c << std::endl;
		Character ch = characters[*c];
		float xpos = x + ch.bearing.x * scale;
		float ypos = y + (characters['H'].bearing.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
		{ xpos, ypos + h, 0.0f, 1.0f },
		{ xpos, ypos, 0.0f, 0.0f },
		{ xpos + w, ypos, 1.0f, 0.0f },
		{ xpos, ypos + h, 0.0f, 1.0f },
		{ xpos + w, ypos, 1.0f, 0.0f },
		{ xpos + w, ypos + h, 1.0f, 1.0f }
		};
// render glyph texture over quad
		//glBindTexture(GL_TEXTURE_2D, ch.textureID);
		ch.texture.bind();
// update content of VBO memory
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		text_vbo.bind();
//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		text_vbo.subbuffer(vertices, sizeof(vertices));
//glBindBuffer(GL_ARRAY_BUFFER, 0);
// render quad
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//std::cout << *c << std::endl;
	// advance cursors for next glyph (advance is 1/64 pixels)
		x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
	}
//glBindVertexArray(0);
//glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawGlyph()
{
	glyphS.use();
	t.bind();
	vaoglyph.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
