#ifndef UICOMPONENT_H
#define UICOMPONENT_H
#include "../gfx/gmath.h"
#include "../gfx/renderer.h"

enum UIState
{
	STATE_DEFAULT,
	STATE_HOVER,
	STATE_CLICK,
	STATE_RELEASE
};
class UIComponent
{
public:
	UIComponent(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
	bool fixed;
	UIState state = STATE_DEFAULT;


	bool collideMouse(glm::vec2 mousePosition);
	virtual void update() = 0;
	virtual void render(Renderer renderer) = 0;
};

#endif
