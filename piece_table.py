class Sequence:

    def __init__(self, filepath):
        self.piece_table = PieceTable()
        self.add_buffer = ""
        #File handling code should be decoupled from the sequence so it should be in its own file
        try:
            with open(filepath, "r") as rf:
                self.file_buffer = rf.read()
        except:
            self.file_buffer = ""
        f = Span(0,0,len(self.file_buffer))
        f.next = self.piece_table.head.next
        self.piece_table.head.next = f
        f.prev = f.next.prev
        f.next.prev = f
        self.undo_stack = Stack()
        self.redo_stack = Stack()
        
    
    def insert(self, index, text):
        old_span = SpanRange()
        self.add_buffer += text
        offset = 0
        sptr = self.piece_table.head.next
        while sptr:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                    #old_span.append(sptr.prev)
                    #old_span.append(sptr)
                    new_span = Span(1, len(self.add_buffer) - len(text), len(text))
                    sptr.prev.next = new_span
                    new_span.prev = sptr.prev
                    new_span.next = sptr
                    sptr.prev = new_span
                else:
                    r_i = index-offset+sptr.start
                    l_span = Span(sptr.buffer, sptr.start, r_i)   
                    new_span = Span(1, len(self.add_buffer) - len(text), len(text))
                    r_span = Span(sptr.buffer, r_i + sptr.start, sptr.length - r_i)
                    sptr.prev.next = l_span
                    l_span.prev = sptr.prev
                    l_span.next = new_span
                    new_span.prev = l_span
                    new_span.next = r_span
                    r_span.prev = new_span
                    r_span.next = sptr.next
                    sptr.next.prev = r_span
                return 1
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0

    def erase(self, index, length):
        sptr = self.piece_table.head.next
        offset = 0
        while sptr.next and length > 0:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                    if sptr.length == 1:
                        sptr.prev.next = sptr.next
                        sptr.next.prev = sptr.prev
                        sptr = sptr.next
                        length -= 1
                    else:
                        sptr.start += 1
                        sptr.length -= 1
                        length -= 1
                elif offset + sptr.length - 1 == index:
                    sptr.length -= 1
                    sptr = sptr.next
                    length -= 1
                    offset += index
                else:
                    r_i = index-offset
                    l_span = Span(sptr.buffer, sptr.start, r_i)   
                    r_span = Span(sptr.buffer, r_i+sptr.start+1, sptr.length - r_i)
                    sptr.prev.next = l_span
                    l_span.prev = sptr.prev
                    l_span.next = r_span
                    r_span.prev = l_span
                    r_span.next = sptr.next
                    sptr.next.prev = r_span#split span in two
                    sptr = r_span
                    length -= 1
                    offset += r_i
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0



    def __str__(self):
        output = ""
        sptr = self.piece_table.head.next
        while sptr.next:
            if not sptr.buffer:
                output += self.file_buffer[sptr.start:sptr.start+sptr.length]
            else:
                output += self.add_buffer[sptr.start:sptr.start+sptr.length]
            sptr = sptr.next
        return output
            




class PieceTable:
    
    def __init__(self):
        self.head = Span(0,0,0)
        self.tail = Span(0,0,1)
        self.head.next = self.tail
        self.tail.prev = self.head

    def __str__(self):
        sptr = self.head.next
        output = ""
        while sptr.next:
            output += str(sptr) + "\n"
            sptr = sptr.next
        return output
            


class Span:

    def __init__(self, buffer, start, length):
        self.next = None
        self.prev = None
        self.buffer = buffer
        self.start = start
        self.length = length

    def copy(self):
        new = Span(self.buffer. self.start, self.length)
        new.next = self.next
        new.prev = self.prev
        return new

    def __str__(self):
       return f"({self.buffer},{self.start},{self.length})"

class Stack:

    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()


class SpanRange:

    def __init__(self):
        self.first = None
        self.last = None
        self.boundary = None
        self.length = 0

    def append(self, span):
        if not self.first and not self.last and not self.boundary:
            self.first = span
            self.last = span
            self.boundary = False
        elif self.first == self.last and not self.boundary:
            self.boundary = True
            self.last = span
        else:
            self.boundary = False
            self.last = span



s = Sequence("test.txt")
print(len(s.file_buffer))
#s.insert(48,"xxxx",3)
#s.insert(2,"yyyy",3)
#s.insert(6,"?",3)
#s.insert(0,"?",3)
#s.erase(2)
#s.erase(5)

s.erase(2,5)
s.erase(1,2)
s.erase(5,10)
#s.insert(2,"?",3)

print(s)
print(s.piece_table)
#print(s.add_buffer)
