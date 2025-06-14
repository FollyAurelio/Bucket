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
        self.undo_stack = []
        self.redo_stack = []
        
    
    def insert(self, index, text):
        self.add_buffer += text
        offset = 0
        sptr = self.piece_table.head.next
        while sptr:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                    new_span = Span(1, len(self.add_buffer) - len(text), len(text))
                    sptr.prev.next = new_span
                    new_span.prev = sptr.prev
                    new_span.next = sptr
                    sptr.prev = new_span
                else:
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
                self.undo_stack.append(("erase", index, text, len(text)))
                return 1
            else:
                offset += sptr.length
                sptr = sptr.next
        return 0

    def get_text(self, buffer, start):
        if buffer == 0:
            return self.file_buffer[start]
        elif buffer == 1:
            return self.add_buffer[start]

    def erase(self, index, length):
        sptr = self.piece_table.head.next
        offset = 0
        text = ""
        l = length
        while sptr.next and length > 0:
            if (offset <= index and index < offset + sptr.length):
                if offset == index:
                    text += self.get_text(sptr.buffer, sptr.start)
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
                    text += self.get_text(sptr.buffer, sptr.length-1)
                    sptr.length -= 1
                    sptr = sptr.next
                    length -= 1
                    offset += index
                else:
                    r_i = index-offset
                    l_span = Span(sptr.buffer, sptr.start, r_i)   
                    r_span = Span(sptr.buffer, r_i+sptr.start+1, sptr.length - r_i)
                    text += self.get_text(sptr.buffer, r_i + sptr.start)
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
        self.undo_stack.append(("insert", index, text, l))
        return 0

    def undo_redo(self, stack): #revert?
        if stack == "undo":
            pop_stack = self.undo_stack
            push_stack = self.redo_stack
        elif stack == "redo":
            push_stack = self.undo_stack
            pop_stack = self.redo_stack
        else:
            return 0
        if len(pop_stack) > 0:
            action = pop_stack.pop()
            if action[0] == "insert":
                self.insert(action[1], action[2]) 
                self.undo_stack.pop()
                #lock the linked list?
                push_stack.append(("erase", action[1], action[2], action[3]))
            elif action[0] == "erase":
                self.erase(action[1], action[3])
                self.undo_stack.pop()
                push_stack.append(("insert", action[1], action[2], action[3]))
            else:
                return 0
            return 1

    def refresh(self):
        self.file_buffer = str(self)
        self.add_buffer = ""
        f = Span(0,0,len(self.file_buffer))
        f.next = self.piece_table.tail
        self.piece_table.head.next = f
        f.prev = self.piece_table.head
        self.piece_table.tail.prev = f
  
 
         


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







s = Sequence("test.tx")
#print(len(s.file_buffer))
#s.insert(2,"!!")
#s.undo()
#s.insert(2,"yyyy")
#s.insert(6,"?",3)
#s.insert(0,"?",3)

#s.erase(1,2)
#s.erase(5,10)
#s.undo()
#s.insert(0,"xxxx")
#s.insert(2,"4")
#s.insert(0,"5")
#s.undo()
#s.undo()
#s.redo()
#s.redo()
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
            s.undo_redo("undo")
        if command[0] == "redo":
            s.undo_redo("redo")
        if command[0] == "refresh":
            s.refresh()
        
        print(s.piece_table)
        print(s)
if __name__ == "__main__":
    main()

#print(s.piece_table)
#print(s.add_buffer)
s = Sequence("tet.txt")
#rf = open("test.txt","r")
#a = rf.read()
#rf.close()
#s.buffer = a
#print(len(s.buffer))
#s.insert(0,  "abcdefghigklmnopkrstuvwxyz")
st = time.time()
s.insert(22222,"1234")
#s.refresh()
en = time.time()
print(en-st)
print(s.piece_table)
#print(s)

