#include "editor.h"

Editor::Editor()
{
	cursor = 0;
	data = "177 this is the base data\n2 inside of the editor";
	mode = MODE_NORMAL;
}

void Editor::render(Renderer renderer)
{
	renderer.drawText(renderer.text_shader, data, glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(1.0f,1.0f,1.0f),false);
}

