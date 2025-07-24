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



class PieceTable
{
public:
	std::string file_buffer;
	std::vector<char> add_buffer;
	size_t length;
	Span *head;
	Span *tail;
	PieceTable();
	PieceTable(std::string s);
	~PieceTable();
	std::string toString();


};
#endif
