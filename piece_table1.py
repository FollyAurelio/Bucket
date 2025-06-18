import time
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
        self.length = len(self.file_buffer)
        
    
    def insert(self, index, text):
        old_span = SpanRange()
        new_span = SpanRange()
        self.add_buffer += text
        offset = 0
        sptr = self.piece_table.head.next
        while sptr:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                    old_span.span_boundary(sptr.prev, sptr)
                    new_span.append(Span(1, len(self.add_buffer) - len(text), len(text)))
                    
                else:
                    r_i = index-offset
                    old_span.append(sptr)
                    new_span.append(Span(sptr.buffer, sptr.start, r_i))
                    new_span.append(Span(1, len(self.add_buffer) - len(text), len(text)))
                    new_span.append(Span(sptr.buffer, r_i + sptr.start, sptr.length - r_i))
                self.swaprange(old_span,new_span)
                self.undo_stack.push(old_span)
                self.length += len(text)
                return 1
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0

    def erase(self, index, length):#change erase
        sptr = self.piece_table.head.next
        old_span = SpanRange()
        new_span = SpanRange()
        offset = 0
        a = length
        while sptr.next:
            if (offset <= index and index < offset + sptr.length):
                r_i = index - offset
                if r_i != 0:
                    new_span.append(Span(sptr.buffer, sptr.start, r_i))
                    if r_i + length < sptr.length:
                        new_span.append(Span(sptr.buffer, sptr.start + r_i + length, sptr.length - r_i - length))
                    length -= min(length, (sptr.length - r_i))
                    old_span.append(sptr)
                    sptr = sptr.next
                break
            offset += sptr.length
            sptr = sptr.next
        while sptr.next and length > 0:
            if length < sptr.length:
                new_span.append(Span(sptr.buffer, sptr.start + length, sptr.length - length))
            length -= min(length, sptr.length)
            old_span.append(sptr)
            sptr = sptr.next
        if new_span.first:
            self.swaprange(old_span, new_span)
        else:
            old_span.first.prev.next = old_span.last.next
            old_span.last.next.prev = old_span.first.prev
        self.undo_stack.push(old_span)
        self.length -= a
        return 1

    def undo(self):
        self.undoredo("undo")

    def redo(self):
        self.undoredo("redo")

    def undoredo(self, action):
        if action == "undo":
            src_stack = self.undo_stack
            dest_stack = self.redo_stack
        elif action == "redo":
            src_stack = self.redo_stack
            dest_stack = self.undo_stack
        else:
            return 0
        if src_stack.is_empty():
            return 0
        range = src_stack.pop()
        dest_stack.push(range)
        if range.boundary:

            first = range.first.next
            last = range.last.prev
            #link the old range
            range.first.next = range.last
            range.last.prev = range.first
            #Store the span range
            range.first = first
            range.last = last
            range.boundary = False
        else:
            first = range.first.prev
            last = range.last.next
            if first.next == last:
                first.next = range.first
                last.prev = range.last
                range.first = first
                range.last = last
                range.boundary = True
            else:
                first = first.next
                last = last.prev
                first.prev.next = range.first
                last.next.prev = range.last
                range.first = first
                range.last = last
                range.boundary = False

    
    def swaprange(self,old, new):
        if old.boundary:
            old.first.next = new.first
            new.first.prev = old.first
            old.last.prev = new.first
            new.first.next = old.last
        else:
            new.first.prev = old.first.prev
            old.first.prev.next = new.first
            old.last.next.prev = new.last
            new.last.next = old.last.next


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
        new = Span(self.buffer, self.start, self.length)
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
    
    def is_empty(self):
        return self.items == []


class SpanRange:

    def __init__(self):
        self.first = None
        self.last = None
        self.boundary = False
        self.length = 0

    def append(self, span):
        if not self.first:
            self.first = span
            self.last = span
        elif self.first:
            self.last.next = span
            span.prev = self.last
            self.last = span

    def span_boundary(self, first, last):
        self.first = first
        self.last = last
        self.boundary = True

    def __str__(self):
        sptr = self.first
        output = ""
        while sptr.next:
            output += str(sptr) + "\n"
            sptr = sptr.next
        return output
     

def main():
    while True:
        command = input().split(" ")
        if command[0] == "insert":
            s.insert(int(command[1]), command[2])
        if command[0] == "erase":
            s.erase(int(command[1]), int(command[2]))
        if command[0] == "undo":
            s.undoredo("undo")
        if command[0] == "redo":
            s.undoredo("redo")
        print(s.length) 
        print(s.piece_table)
        print(s)
if __name__ == "__main__":
    main()


