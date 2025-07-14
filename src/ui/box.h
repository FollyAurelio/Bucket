#ifndef BOX_H
#define BOX_H
#include "UIComponent.h"

class Box : public UIComponent
{
public:
	Box(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool fixed);
	void update();
	void render(Renderer renderer);
};

#endif
