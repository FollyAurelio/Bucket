#include "editor.h"

Editor::Editor()
{
	cursor = 0;
	cursor_col = 0;
	mode = MODE_NORMAL;
}

void Editor::init(std::string text)
{
	sequence = new PieceTable(text);
	reline();
}

void Editor::save()
{
	writeFile(file_path.c_str(), sequence->toString().c_str());
}

void Editor::backspace()
{
	if(cursor == 0) return;
	if(cursor > sequence->length){
		cursor = sequence->length;
	}
	sequence->erase(cursor - 1, 1);
	cursor -= 1;
	reline();
}

void Editor::remove()
{
	if(cursor >= sequence->length) return;
	sequence->erase(cursor, 1);
	reline();
}

void Editor::insert(char character, size_t length)
{
	sequence->insert(cursor, &character, length);
	cursor += length;
	reline();
}
void Editor::enter()
{
	char newline = '\n';
	sequence->insert(cursor, &newline, 1);
	cursor += 1;
	reline();
}

void Editor::move_char_left()
{
	if(cursor > lines[cursor_row()].begin) {
		cursor -= 1;
		cursor_col = cursor - lines[cursor_row()].begin;
	}

}

void Editor::move_line_up()
{
	size_t row = cursor_row();
	if(row > 0){
		Line next_line = lines[row - 1];
		size_t next_line_size = next_line.end - next_line.begin;
		if(cursor_col > next_line_size)
			cursor = next_line.begin + next_line_size;
		else
			cursor = next_line.begin + cursor_col;
	}
}
void Editor::move_line_down()
{
	size_t row = cursor_row();
	if(row < lines.size() - 1){
		Line next_line = lines[row + 1];
		size_t next_line_size = next_line.end - next_line.begin;
		if(cursor_col > next_line_size)
			cursor = next_line.begin + next_line_size;
		else
			cursor = next_line.begin + cursor_col;

	}
}

void Editor::move_char_right()
{
	if(cursor < lines[cursor_row()].end){
		cursor += 1;
		cursor_col = cursor - lines[cursor_row()].begin;
	}
	
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
	size_t j = 0;
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
				line.end = j;
				lines.push_back(line);
				line.begin = j + 1;
			}
			j++;
		}
	}
	line.end = sequence->length;
	lines.push_back(line);
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

void Editor::undo()
{
	sequence->undo_redo(0);
	reline();
}

void Editor::redo()
{
	sequence->undo_redo(1);
	reline();
}

void Editor::draw_cursor(size_t cursor_position, Renderer renderer, glm::vec4 color)
{
	char char_at_pos = sequence->get_char_at(cursor_position);
	char c;
	size_t row;
	size_t total_lines = lines.size();
	for(size_t j = 0; j < total_lines;j++){
		Line line = lines[j];
		if(line.begin <= cursor_position && cursor_position <=line.end){
			row = j;
			break;
		}
	}
	//size_t col = cursor - lines[row].begin;
	unsigned int advance = 0;
	for(size_t i = lines[row].begin; i < cursor_position; i++){
		c = sequence->get_char_at(i);
		if(c == '	'){
			advance += (renderer.font.characters[' '].advance >> 6) * 4;
		}
		else{
			advance += renderer.font.characters[sequence->get_char_at(i)].advance >> 6;
		}
	}
	float horizontal_offset = advance;
	float vertical_offset = renderer.font.lineoffset * row;
	float cursor_width = mode == MODE_INSERT ?renderer.font.characters[char_at_pos].bearing.x : renderer.font.characters[char_at_pos].size.x + renderer.font.characters[char_at_pos].bearing.x;

	if(cursor_width == 0)
		cursor_width = 1.0f;
	if(char_at_pos == ' ' && (mode == MODE_NORMAL || mode == MODE_SELECT))
		cursor_width = renderer.font.characters[char_at_pos].advance >> 6;
	if(char_at_pos == '	' && (mode == MODE_NORMAL || mode == MODE_SELECT))
		cursor_width = (renderer.font.characters[' '].advance >> 6) * 4;
	float cursor_height = renderer.font.lineoffset;
	glm::vec4 cursor_color = color;
	//render cursor
	renderer.drawRectangle(renderer.rect_shader, glm::vec2(180.0f + horizontal_offset,12.5f + vertical_offset), glm::vec2(cursor_width, cursor_height), cursor_color , false);
}


void Editor::render(Renderer &renderer)
{
	//get cursor values
	char char_at_pos = sequence->get_char_at(cursor);
	char c;
	size_t row = cursor_row();
	//size_t col = cursor - lines[row].begin;
	unsigned int advance = 0;
	for(size_t i = lines[row].begin; i < cursor; i++){
		c = sequence->get_char_at(i);
		if(c == '	'){
			advance += (renderer.font.characters[' '].advance >> 6) * 4;
		}
		else{
			advance += renderer.font.characters[sequence->get_char_at(i)].advance >> 6;
		}
	}
	float horizontal_offset = advance;
	float vertical_offset = renderer.font.lineoffset * row;
	float cursor_width = mode == MODE_INSERT ?renderer.font.characters[char_at_pos].bearing.x : renderer.font.characters[char_at_pos].size.x + renderer.font.characters[char_at_pos].bearing.x;

	if(cursor_width == 0)
		cursor_width = 1.0f;
	if(char_at_pos == ' ' && (mode == MODE_NORMAL || mode == MODE_SELECT))
		cursor_width = renderer.font.characters[char_at_pos].advance >> 6;
	if(char_at_pos == '	' && (mode == MODE_NORMAL || mode == MODE_SELECT))
		cursor_width = (renderer.font.characters[' '].advance >> 6) * 4;
	float cursor_height = renderer.font.lineoffset;
	glm::vec4 cursor_color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	//render cursor
	renderer.drawRectangle(renderer.rect_shader, glm::vec2(180.0f + horizontal_offset,12.5f + vertical_offset), glm::vec2(cursor_width, cursor_height), cursor_color , false);
	//render selection
	if(mode == MODE_SELECT){
		if(select_begin < cursor){
			for(size_t i = select_begin; i < cursor; i++){
			draw_cursor(i, renderer, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));
			}
		}
		else{
			for(size_t i = select_begin; i > cursor; i--){
			draw_cursor(i, renderer, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));
			}
		}

	}
	

	//render line numbers
	size_t total_lines = lines.size();
	for(size_t i = 0 ; i <total_lines; i++)
	{
		renderer.drawText(renderer.text_shader, std::string(5-std::to_string(i+1).length(), ' ') + std::to_string(i + 1), glm::vec2(25.0f, 25.0f + renderer.font.lineoffset * i), 1.0f, glm::vec4(1.0f,1.0f,1.0f,0.5f), false);
	}
	//render text
	renderer.drawEditorText(renderer.text_shader, sequence, glm::vec2(180.0f, 25.0f), 1.0f, glm::vec4(1.0f,1.0f,1.0f, 1.0f),false);
	//set Camera
	glm::vec4 cursorPos = renderer.camera * glm::vec4(horizontal_offset + 180.0f, vertical_offset, 0.0f, 1.0f);
	if(cursorPos.y > renderer.screen.y){
		renderer.cameraPosition.y -= 1;
	}
	if(cursorPos.y < 0){
		renderer.cameraPosition.y += 1;
	}
	if(cursorPos.x > renderer.screen.x){
		renderer.cameraPosition.x -= 1;
	}
	if(cursorPos.x < 0){
		renderer.cameraPosition.x += 1;
	}
	//renderer.cameraPosition.y = 1.0f - cursor_row();
	//renderer.cameraPosition.x = 1.0f - advance;
	
}

