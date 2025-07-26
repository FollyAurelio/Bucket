#ifndef EDITOR_H
#define EDITOR_H
#include "util.h"
#include "renderer.h"
#include "piece_table.h"


enum EditorMode
{
	MODE_NORMAL,
	MODE_INSERT,
	MODE_SELECT,
};

struct Line
{
	size_t begin;
	size_t end;
};

class Editor
{
public:
	std::vector<Line> lines;
	EditorMode mode;
	size_t cursor;
	std::string data;
	PieceTable *sequence;
	size_t select_begin;
	std::string file_path;
	std::string clipboard;

	Editor();
	~Editor();
	void init(std::string text);
	void insert(char character);
	void backspace();
	void move_char_left();
	void move_char_right();
	void move_line_up();
	void move_line_down();
	void enter();
	size_t cursor_row();
	void reline();
	void remove();
	void render(Renderer renderer);
};

#endif
