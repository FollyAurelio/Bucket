#ifndef UICOMPONENT_H
#define UICOMPONENT_H
#include "../gfx/gmath.h"
#include "../gfx/renderer.h"

class UIComponent
{
public:
	UIComponent(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
	bool fixed;

	virtual void update() = 0;
	virtual void render(Renderer *renderer) = 0;
};

#endif
