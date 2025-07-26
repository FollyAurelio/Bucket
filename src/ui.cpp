#include "ui.h"

UIComponent::UIComponent(glm::vec2 position, glm::vec2 size, glm::vec4 color, bool fixed)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->fixed = fixed;
}

bool UIComponent::collideMouse(glm::vec2 mousePosition)
{
	if(mousePosition.x >= position.x && mousePosition.x <= position.x + size.x && mousePosition.y >= position.y && mousePosition.y <= position.y + size.y)
	{
		return true;
	}
	return false;
}

Box::Box(glm::vec2 position, glm::vec2 size, glm::vec4 color, bool fixed)
	:UIComponent(position, size, color, fixed){}

void Box::update()
{
	switch(state)
	{
		case STATE_DEFAULT:
			color = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
			break;
		case STATE_HOVER:
			color = glm::vec4(0.0f, 0.0f, 0.7f, 1.0f);
			break;
		case STATE_CLICK:
			color = glm::vec4(0.7f, 0.0f, 0.0f, 1.0f);
			break;
		case STATE_RELEASE:
			std::cout << "Hello World" << std::endl;
			state = STATE_DEFAULT; 
			break;
		default:
			break;
	}	
}
void Box::render(Renderer renderer)
{
	renderer.drawRectangle(renderer.rect_shader, position, size, color, fixed);
}

