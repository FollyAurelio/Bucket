class Sequence:

    def __init__(self):
        self.piece_table = PieceTable()
        self.file_buffer = ""
        self.add_buffer = ""
    
    def insert(self):
        pass

    def erase(self):
        pass


class PieceTable:
    
    def __init__(self):
        self.head = Span(0,0,0)
        self.tail = Span(0,0,0)
        self.head.next = self.tail
        self.tail.prev = self.head


class Span:

    def __init__(self, buffer, start, length):
        self.next = None
        self.prev = None
        self.buffer = buffer
        self.start = start
        self.length = length

def print_piece_table(sequence):
    sptr = sequence.piece_table.head.next
    while sptr.next:
        if not sptr.buffer:
            print(sequence.file_buffer[sptr.start:sptr.start+sptr.length], end="")
        else:
            print(sequence.add_buffer[sptr.start:sptr.start+sptr.length], end="")
        sptr = sptr.next


s = Sequence()
s.file_buffer = "The brown fox jumped over the lazy dog.\nThe end"
f = Span(0,0,47)
s.piece_table.head.next.prev = f
s.piece_table.head.next = f
f.prev = s.piece_table.head
f.next = s.piece_table.tail
print_piece_table(s)
