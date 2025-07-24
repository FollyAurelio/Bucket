#include "piece_table.h"

Span::Span(bool buffer, size_t start, size_t length)
{
	this->buffer = buffer;
	this->start = start;
	this->length = length;
}


PieceTable::PieceTable()
{
}



PieceTable::PieceTable(std::string s)
{
	head = new Span(0, 0, 0);
	tail = new Span(0, 0, 1);
	head->next = tail;
	tail->prev = head;
	file_buffer = s;
	length = s.length();
	Span *f = new Span(0, 0, length);
	f->next = tail;
	f->prev = head;
	head->next = f;
	tail->prev = f;
}

PieceTable::~PieceTable()
{
	Span *sptr, *tmp;
	for(sptr = head->next; sptr != tail; sptr = tmp)
	{
		tmp = sptr->next;
		delete sptr;
	}
	delete head;
	delete tail;
}

std::string PieceTable::toString()
{
	std::string output;
	Span *sptr;
	for(sptr = head->next; sptr->next;sptr = sptr->next)

	{
		if(!sptr->buffer)
		{
			for(size_t i = sptr->start; i < sptr->start + sptr->length; i++)
			{
				output += file_buffer[i];
			}
		}
		else
		{
			for(size_t i = sptr->start; i < sptr->start + sptr->length; i++)
			{
				output += add_buffer[i];
			}
		}
	}
	return output;
}

