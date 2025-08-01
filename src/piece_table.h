#ifndef PIECE_TABLE_H
#define PIECE_TABLE_H
#include "util.h"

struct Span
{
	Span *prev;
	Span *next;
	bool buffer;
	size_t start;
	size_t length;

	Span(bool buffer, size_t start, size_t length);
};

struct SpanRange
{
	Span *first = nullptr;
	Span *last = nullptr;
	size_t length;
	void free();
	bool boundary;
	void append(Span *span);
	void span_boundary(Span *before, Span *after);
};



class PieceTable
{
public:
	std::string file_buffer;
	std::vector<char> add_buffer;
	size_t length;
	Span *head;
	Span *tail;
	std::stack<SpanRange*> undostack;
	std::stack<SpanRange*> redostack;
	size_t last_insert;
	PieceTable();
	PieceTable(std::string s);
	~PieceTable();
	void clearstack(std::stack<SpanRange*> &s);
	char get_char_at(size_t index);
	void insert(size_t index, const char *text, size_t size);
	void erase(size_t index, size_t size);
	void swaprange(SpanRange *src, SpanRange *dest);
	void undo_redo(int action);
	std::string toString();


};
#endif
