#ifndef EDITOR_H
#define EDITOR_H
#include <vector>

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

	render(Renderer renderer);
};
