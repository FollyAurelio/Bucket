#include "editor.h"

Editor::Editor()
{
	cursor = 0;
	mode = MODE_NORMAL;
}

void Editor::init(std::string text)
{
	sequence = new PieceTable(text);
	sequence->insert(20, "c", 1);
	sequence->insert(21, "asd", 3);
	std::cout << sequence->toString() << std::endl;
	reline();
}

Editor::~Editor()
{
	delete sequence;
}

void Editor::reline()
{
	lines.clear();
	Line line;
	line.begin = 0;
	Span *sptr;
	char c;
	for(sptr = sequence->head->next; sptr->next; sptr = sptr->next){
		for(size_t i = sptr->start; i < sptr->start + sptr->length; i++){
			if(!sptr->buffer){
				c = sequence->file_buffer[i];
			}
			else{
				c = sequence->add_buffer[i];
			}
			if(c == '\n'){
				line.end = i;
				lines.push_back(line);
				line.begin = i + 1;
			}
		}
	}
	//line.end = sequence->length;
	//lines.push_back(line);
}

void Editor::render(Renderer renderer)

{
	//get cursor position

	//render line numbers
	for(size_t i = 0 ; i <lines.size(); i++)
	{
		renderer.drawText(renderer.text_shader, std::string(5-std::to_string(i+1).length(), ' ') + std::to_string(i + 1), glm::vec2(25.0f, 25.0f + renderer.font.lineoffset * i), 1.0f, glm::vec4(1.0f,1.0f,1.0f,0.5f), false);
	}
	//render text
	renderer.drawEditorText(renderer.text_shader, sequence, glm::vec2(180.0f, 25.0f), 1.0f, glm::vec4(1.0f,1.0f,1.0f, 1.0f),false);
	//render cursor
	
}

