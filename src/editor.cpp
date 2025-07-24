#include "editor.h"

Editor::Editor()
{
	cursor = 0;
	data = "  177 this is the base data\n    2 inside of the editor";
	mode = MODE_NORMAL;
}

void Editor::render(Renderer renderer)

{
	for(int i = 0 ; i < 10000; i++)
	{
		renderer.drawText(renderer.text_shader, std::string(5-std::to_string(i+1).length(), ' ') + std::to_string(i + 1), glm::vec2(25.0f, 25.0f + renderer.font.lineoffset * i), 1.0f, glm::vec4(1.0f,1.0f,1.0f,0.5f), false);
	}
	renderer.drawText(renderer.text_shader, data, glm::vec2(150.0f, 25.0f), 1.0f, glm::vec4(1.0f,1.0f,1.0f, 1.0f),false);
}

