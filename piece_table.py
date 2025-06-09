class Sequence:

    def __init__(self, filepath):
        self.piece_table = PieceTable()
        self.add_buffer = ""
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
        
    
    def insert(self, index, text, seq_length):
        new_span = Span(1, len(self.add_buffer), len(text))
        old_span = SpanRange()
        self.add_buffer += text
        offset = 0
        sptr = self.piece_table.head.next
        while sptr:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                   #old_span.append(sptr.prev)
                   #old_span.append(sptr)
                   sptr.prev.next = new_span
                   new_span.prev = sptr.prev
                   new_span.next = sptr
                   sptr.prev = new_span
                else:
                    pass
                return 1
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0

        """ if offset == index:
                    pass
                else:
                    pass"""
            

        

    def erase(self):
        pass

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


class Span:

    def __init__(self, buffer, start, length):
        self.next = None
        self.prev = None
        self.buffer = buffer
        self.start = start
        self.length = length

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
s.insert(45,"Or is it?",3)
print(s)
