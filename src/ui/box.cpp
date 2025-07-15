#include "box.h"

Box::Box(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed)
	:UIComponent(position, size, color, fixed){}
void Box::update()
{
	switch(state)
	{
		case STATE_DEFAULT:
			color = glm::vec3(0.0f, 0.7f, 0.0f);
			break;
		case STATE_HOVER:
			color = glm::vec3(0.0f, 0.0f, 0.7f);
			break;
		case STATE_CLICK:
			color = glm::vec3(0.7f, 0.0f, 0.0f);
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
	renderer.drawRectangle(position, size, color, fixed);
}

