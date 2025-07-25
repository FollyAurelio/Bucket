#include "editor.h"

Editor::Editor()
{
	cursor = 0;
	data = "  177 this is the base data\n    2 inside of the editor";
	mode = MODE_NORMAL;
	sequence = new PieceTable("me and you\nforever\n\n\n\n\n\n\n\n\n\na");
	sequence->insert(19, "asd", 3);
}

Editor::~Editor()
{
	delete sequence;
}

void Editor::render(Renderer renderer)

{
	//render line numbers
	for(int i = 0 ; i < 10000; i++)
	{
		renderer.drawText(renderer.text_shader, std::string(5-std::to_string(i+1).length(), ' ') + std::to_string(i + 1), glm::vec2(25.0f, 25.0f + renderer.font.lineoffset * i), 1.0f, glm::vec4(1.0f,1.0f,1.0f,0.5f), false);
	}
	//render text
	renderer.drawEditorText(renderer.text_shader, sequence, glm::vec2(180.0f, 25.0f), 1.0f, glm::vec4(1.0f,1.0f,1.0f, 1.0f),false);
	//render cursor
	
}

