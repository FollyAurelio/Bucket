#ifndef UICOMPONENT_H
#define UICOMPONENT_H
#include "util.h"
#include "renderer.h"

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

class Box : public UIComponent
{
public:
	Box(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	void update();
	void render(Renderer renderer);
};


#endif
