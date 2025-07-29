#include "renderer.h"

Renderer::Renderer(float windowWidth, float windowHeight)
{	
	projection = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
		
}	

void Renderer::init()
{
	glGenBuffers(1, &rect_vbo);
	glGenVertexArrays(1, &rect_vao);
	glGenBuffers(1, &rect_ebo);
	glBindVertexArray(rect_vao);
	glBindBuffer(GL_ARRAY_BUFFER, rect_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &text_vbo);
	glGenVertexArrays(1, &text_vao);
	glBindVertexArray(text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(text_vertices), text_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	font = loadFont("res/fonts/Antonio-Regular.ttf");

	camera = glm::mat4(1.0f);
	inverseCamera = glm::mat4(1.0f);
	no_camera = glm::mat4(1.0f);
	
	rect_shader.init();
	text_shader.init();
}

void Renderer::setCamera()
{
	camera = glm::mat4(1.0f);
	camera = glm::translate(camera, glm::vec3(cameraPosition.x * 100.0f, cameraPosition.y * font.lineoffset, 0.0f));
	camera = glm::scale(camera, glm::vec3(cameraZoom, cameraZoom, 1.0f));
	inverseCamera = glm::inverse(camera);
}

void Renderer::drawRectangle(Shader shader, glm::vec2 position, glm::vec2 size, glm::vec4 color, bool fixed)
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));
	shader.setMatrix4("model", model);
	if (fixed)
	{
		shader.setMatrix4("view", no_camera);
	}
	else
	{
		shader.setMatrix4("view", camera);
	}
	shader.setMatrix4("projection", projection);
	shader.setVector4("color", color);
	glBindVertexArray(rect_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::drawText(Shader shader, std::string text, glm::vec2 position, float scale, glm::vec4 color, bool fixed)
//TODO : optimize this method
{
	shader.use();
	shader.setInt("text", 0);
	shader.setVector4("textColor", color);
	if (fixed)
		shader.setMatrix4("view", no_camera);
	else
		shader.setMatrix4("view", camera);
	shader.setMatrix4("projection", projection);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_vao);
	glm::mat4 model;
	std::string::const_iterator c;
	float copyX = position.x;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = font.characters[*c];
		if(*c == '\n')
		{
			position.y += font.lineoffset * scale;
			position.x = copyX;
		}
		else if(*c == ' '){
			position.x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64
		}
		else{
			float xpos = position.x + ch.bearing.x * scale;
			float ypos = position.y + (font.characters['H'].bearing.y - ch.bearing.y) * scale;
			model = glm::translate(glm::mat4(1.0f),glm::vec3(xpos,ypos,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.size.x * scale, ch.size.y * scale, 0));
			shader.setMatrix4("model", model);
			glBindTexture(GL_TEXTURE_2D, ch.texture);
			glBindBuffer(GL_ARRAY_BUFFER,text_vbo);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
			position.x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
		}
	}
}

void Renderer::drawEditorText(Shader shader, PieceTable *sequence, glm::vec2 position, float scale, glm::vec4 color, bool fixed)
//TODO : optimize this method
{
	shader.use();
	shader.setInt("text", 0);
	shader.setVector4("textColor", color);
	if (fixed)
		shader.setMatrix4("view", no_camera);
	else
		shader.setMatrix4("view", camera);
	shader.setMatrix4("projection", projection);
	glm::mat4 model;
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_vao);
	Span *sptr;
	float copyX = position.x;
	char c;
	for(sptr = sequence->head->next; sptr->next; sptr = sptr->next){
		for(size_t i = sptr->start; i < sptr->start + sptr->length; i++){
			if(!sptr->buffer){
				c = sequence->file_buffer[i];
			}
			else{
				c = sequence->add_buffer[i];
			}
			Character ch = font.characters[c];
			if(c == '\n')
			{
				position.y += font.lineoffset * scale;
				position.x = copyX;
			}
			else if(c == ' ' ){
				position.x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64
			}
			else if(c == '	'){
				position.x += (font.characters[' '].advance >> 6) * scale * 4;
			}
			else{
				float xpos = position.x + ch.bearing.x * scale;
				float ypos = position.y + (font.characters['H'].bearing.y - ch.bearing.y) * scale;
				model = glm::translate(glm::mat4(1.0f),glm::vec3(xpos,ypos,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.size.x * scale, ch.size.y * scale, 0));
				shader.setMatrix4("model", model);
				glBindTexture(GL_TEXTURE_2D, ch.texture);
				glBindBuffer(GL_ARRAY_BUFFER,text_vbo);
				glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
				position.x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
			}
		}
	}
}
