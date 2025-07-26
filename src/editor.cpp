#include "editor.h"

Editor::Editor()
{
	cursor = 1;
	mode = MODE_NORMAL;
}

void Editor::init(std::string text)
{
	sequence = new PieceTable(text);
	sequence->insert(20, "c", 1);
	sequence->insert(21, "asd", 3);
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

size_t Editor::cursor_row()
{
	size_t total_lines = lines.size();
	for(size_t row = 0; row < total_lines; row++){
		Line line = lines[row];
		if(line.begin <= cursor && cursor <= line.end){
			return row;
		}
	}
	return total_lines - 1;
}


void Editor::render(Renderer renderer)

{
	//get cursor values
	char char_at_pos = sequence->get_char_at(cursor);
	size_t row = cursor_row();
	//size_t col = cursor - lines[row].begin;
	unsigned int advance = 0;
	for(size_t i = lines[row].begin; i < cursor; i++){
		advance += renderer.font.characters[sequence->get_char_at(i)].advance >> 6;
	}
	float horizontal_offset = advance;
	float vertical_offset = renderer.font.lineoffset * row;
	float cursor_width = mode == MODE_INSERT ?renderer.font.characters[char_at_pos].bearing.x : renderer.font.characters[char_at_pos].size.x;

	if(cursor_width == 0)
		cursor_width = 1.0f;
	float cursor_height = renderer.font.lineoffset;
	glm::vec4 cursor_color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	//render cursor
	renderer.drawRectangle(renderer.rect_shader, glm::vec2(180.0f + horizontal_offset,12.5f + vertical_offset), glm::vec2(cursor_width, cursor_height), cursor_color , false);

	//render line numbers
	size_t total_lines = lines.size();
	for(size_t i = 0 ; i <total_lines; i++)
	{
		renderer.drawText(renderer.text_shader, std::string(5-std::to_string(i+1).length(), ' ') + std::to_string(i + 1), glm::vec2(25.0f, 25.0f + renderer.font.lineoffset * i), 1.0f, glm::vec4(1.0f,1.0f,1.0f,0.5f), false);
	}
	//render text
	renderer.drawEditorText(renderer.text_shader, sequence, glm::vec2(180.0f, 25.0f), 1.0f, glm::vec4(1.0f,1.0f,1.0f, 1.0f),false);
	//render cursor
	
}

