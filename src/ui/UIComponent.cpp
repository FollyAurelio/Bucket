#include "UIComponent.h"

UIComponent::UIComponent(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->fixed = fixed;
}

void UIComponent::render(Renderer *renderer)
{
	renderer->drawRectangle(position, size, color, fixed);
}
void UIComponent::onClick(){}
void UIComponent::onHover(){}

