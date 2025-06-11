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
                    if not sptr == self.piece_table.head.next:
                        old_span.append(sptr.prev.copy())
                    if not sptr == self.piece_table.tail:
                        old_span.append(sptr.copy())
                    new_span = Span(1, len(self.add_buffer) - len(text), len(text))
                    sptr.prev.next = new_span
                    new_span.prev = sptr.prev
                    new_span.next = sptr
                    sptr.prev = new_span
                else:
                    old_span.append(sptr.copy())
                    r_i = index-offset
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
                self.undo_stack.push(old_span)
                return 1
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0

    def erase(self, index, length):
        sptr = self.piece_table.head.next
        old_span = SpanRange()
        offset = 0
        while sptr.next:
            if offset < length + index or offset >= index:
                old_span.append(sptr.copy())
            offset += sptr.length
            sptr = sptr.next
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
        self.undo_stack.push(old_span)
        return 0

    def undo(self):
        if not self.undo_stack.is_empty():
            new_span = SpanRange()
            old_span = self.undo_stack.pop()
            sptr = old_span.first.prev.next
            while sptr != old_span.last.next:
                new_span.append(sptr.copy())
                sptr = sptr.next
            self.redo_stack.push(new_span)
            old_span.first.prev.next = old_span.first
            old_span.last.next.prev = old_span.last

    def redo(self):
        if not self.redo_stack.is_empty():
            new_span = SpanRange()
            old_span = self.redo_stack.pop()
            sptr = old_span.first.prev.next
            while sptr != old_span.last.next:
                try:
                    new_span.append(sptr.copy())
                except:
                    print(old_span.last.next)
                sptr = sptr.next
            self.undo_stack.push(new_span)
            old_span.first.prev.next = old_span.first
            old_span.last.next.prev = old_span.last
         


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
        #self.boundary = None
        self.length = 0

    def append(self, span):
        if not self.first:
            self.first = span
            self.last = span
        elif self.first:
            self.last.next = span
            span.prev = self.last
            self.last = span




s = Sequence("tt.txt")
#print(len(s.file_buffer))
#s.insert(2,"!!")
#s.undo()
#s.insert(2,"yyyy")
#s.insert(6,"?",3)
#s.insert(0,"?",3)
#s.erase(2)
#s.erase(5)

#s.erase(1,2)
#s.erase(5,10)
#s.undo()
#s.insert(2,"?")
#s.insert(2,"x")
#s.insert(0,"oo")
#s.erase(1,2)
#s.erase(0,1)
#s.insert(5,"x")
def main():
    while True:
        command = input().split(" ")
        if command[0] == "insert":
            s.insert(int(command[1]), command[2])
        if command[0] == "erase":
            s.erase(int(command[1]), int(command[2]))
        if command[0] == "undo":
            s.undo()
        if command[0] == "redo":
            s.redo()
        
        print(s.piece_table)
        print(s)
if __name__ == "__main__":
    main()
#print(s)
#print(s.piece_table)
#print(s.add_buffer)
