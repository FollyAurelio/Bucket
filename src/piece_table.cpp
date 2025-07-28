#include "piece_table.h"

Span::Span(bool buffer, size_t start, size_t length)
{
	this->buffer = buffer;
	this->start = start;
	this->length = length;
	this->next = nullptr;
	this->prev = nullptr;
}

//We don't want a destructor for spanranges, as some of them are stack allocated to help with some functions, and thus the destructor would free the spans inside of them when they went out of scope (memory management is complicated)
void SpanRange::free()
{
	if(!boundary){
		Span *sptr, *next, *term;
		for(sptr = first, term = last->next; sptr && sptr != term; sptr = next){
			next = sptr->next;
			delete sptr;
		}
	}
}

void SpanRange::append(Span *span)
{
	if(!first){
		first = span;
	}
	else if(first){
		last->next = span;
		span->prev  = last;
	}
	last = span;
}

void SpanRange::span_boundary(Span *before, Span *after)
{
	first = before;
	last = after;
	boundary = true;
}


PieceTable::PieceTable(std::string s)
{
	last_insert = -1;
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
	for(sptr = head->next; sptr->next; sptr = tmp){
		tmp = sptr->next;
		delete sptr;
	}
	delete head;
	delete tail;
	clearstack(undostack);
	clearstack(redostack);
}

void PieceTable::clearstack(std::stack<SpanRange*> &s)
{
	while(!s.empty()){
		//pop doesn't return the value for whatever reason (shit language)
		SpanRange *range = s.top();
		s.pop();
		range->free();
		delete range;
	}
}

void PieceTable::swaprange(SpanRange *src, SpanRange *dest)
{
	if(src->boundary){
		src->first->next = dest->first;
		dest->first->prev = src->first;
		src->last->prev = dest->first;
		dest->first->next = src->last;
	}
	else{
		dest->first->prev = src->first->prev;
		src->first->prev->next = dest->first;
		src->last->next->prev = dest->last;
		dest->last->next = src->last->next;
	}
}

char PieceTable::get_char_at(size_t index)
{
	Span *sptr;
	size_t offset = 0;
	for(sptr = head->next; sptr->next; sptr = sptr->next){
		if(offset <= index && index < offset + sptr->length){
			size_t r_i = index - offset;
			if(!sptr->buffer){
				return file_buffer[sptr->start + r_i];
			}
			else{
				return add_buffer[sptr->start + r_i];
			}
		}
		offset += sptr->length;
	}
	return 'a';
}



		


void PieceTable::insert(size_t index, const char *text, size_t size)
{
	SpanRange *old_span = new SpanRange();
	old_span->length = length;
	SpanRange new_span;
	for(size_t i = 0; i < size; i++){
		add_buffer.push_back(text[i]);
	}
	size_t offset = 0;
	Span *sptr;
	for(sptr = head->next; sptr; sptr = sptr->next){
		if(offset <= index && index < offset + sptr->length){
			if(offset == index){
				if(last_insert == index){
					sptr->prev->length += size;
				}
				else{
					old_span->span_boundary(sptr->prev, sptr);
					new_span.append(new Span(true, add_buffer.size() - size, size));
					swaprange(old_span, &new_span);
					undostack.push(old_span);

				}
			}
			else{
				size_t r_i = index - offset;
				old_span->append(sptr);
				new_span.append(new Span(sptr->buffer, sptr->start, r_i));
				new_span.append(new Span(true, add_buffer.size() - size, size));
				new_span.append(new Span(sptr->buffer, r_i + sptr->start, sptr->length - r_i));
				swaprange(old_span, &new_span);
				undostack.push(old_span);
			}
			length += size;
			last_insert = index + size;
			return;
		}
		else{
			offset += sptr->length;
		}
	}
}


void PieceTable::erase(size_t index, size_t size)
{
	Span *sptr;
	SpanRange *old_span = new SpanRange();
	old_span->length = length;
	SpanRange new_span;
	size_t offset = 0;
	size_t temp_size = size;
	for(sptr = head->next;sptr->next; sptr = sptr->next){
		if(offset <= index && index < offset + sptr->length){
			size_t r_i = index - offset;
			if(r_i != 0){
				new_span.append(new Span(sptr->buffer, sptr->start, r_i));
				if(r_i + size < sptr->length){
					new_span.append(new Span(sptr->buffer, sptr->start + r_i + size, sptr->length - r_i - size));
				}
				size -= std::min(size, sptr->length - r_i);
				old_span->append(sptr);
				sptr = sptr->next;
			}
			break;
		}
		offset += sptr->length;
	}
	for(; sptr->next && size > 0; sptr = sptr->next){
		if(size < sptr->length){
			new_span.append(new Span(sptr->buffer, sptr->start + size, sptr->length - size));
		}
		size -= std::min(size, sptr->length);
		old_span->append(sptr);
	}
	if(new_span.first){
		swaprange(old_span, &new_span);
	}
	else{
		old_span->first->prev->next = old_span->last->next;
		old_span->last->next->prev = old_span->first->prev;
	}
	undostack.push(old_span);
	length -= temp_size;
	last_insert = -1;
}

void PieceTable::undo_redo(int action)
{
	std::stack<SpanRange*> *src_stack;
	std::stack<SpanRange*> *dest_stack;
	if(action == 0){
		src_stack = &undostack;
		dest_stack = &redostack;
	}
	else if(action == 1){
		src_stack = &redostack;
		dest_stack = &undostack;
	}
	else{
		return;
	}
	if(src_stack->empty()){
		std::cout << "jj" << std::endl;
		return;
	}
	SpanRange *range = src_stack->top();
	size_t temp_length = length;
	length = range->length;
	range->length = temp_length;
	src_stack->pop();
	dest_stack->push(range);
	Span *first, *last;
	if(range->boundary){
		first = range->first->next;
		last = range->last->prev;
		//link the old range
		range->first->next = range->last;
		range->last->prev = range->first;
		//Store the span range
		range->first = first;
		range->last = last;
		range->boundary = false;
	}
	else{
		first = range->first->prev;
		last = range->last->next;
		if(first->next == last){
			first->next = range->first;
			last->prev = range->last;
			range->first = first;
			range->last = last;
			range->boundary = true;
		}
		else{
			first = first->next;
			last = last->prev;
			first->prev->next = range->first;
			last->next->prev = range->last;
			range->first = first;
			range->last = last;
			range->boundary = false;
		}
	}
}

std::string PieceTable::toString()
{
	std::string output;
	Span *sptr;
	for(sptr = head->next; sptr->next;sptr = sptr->next){
		if(!sptr->buffer){
			for(size_t i = sptr->start; i < sptr->start + sptr->length; i++){
				output += file_buffer[i];
			}
		}
		else{
			for(size_t i = sptr->start; i < sptr->start + sptr->length; i++){
				output += add_buffer[i];
			}
		}
	}
	return output;
}

