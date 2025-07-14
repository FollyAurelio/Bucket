#include "UIComponent.h"

UIComponent::UIComponent(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed)
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



