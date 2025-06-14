import time
class Sequence:

    def __init__(self):

        self.buffer = ""
        self.undo_stack = []
        self.redo_stack = []


    def insert(self, index, text):
        self.buffer = self.buffer[0:index] + text + self.buffer[index::]
        self.undo_stack.append(("erase", index, text, len(text)))

    def erase(self, index, length):
        self.buffer = self.buffer[0:index] + self.buffer[index + length ::]
        self.undo_stack.append(("insert", index, self.buffer[index:index+length], length))


    def undo_redo(self, stack):
        if stack == "undo":
            pop_stack = self.undo_stack
            push_stack = self.redo_stack
        elif stack == "redo":
            push_stack = self.undo_stack
            pop_stack = self.redo_stack
        else:
            return 0
        action = pop_stack.pop()
        if action[0] == "insert":
            self.insert(action[1], action[2])
            push_stack.append(("erase", action[1], action[2], action[3]))
        elif action[0] == "erase":
            self.erase(action[1], action[3])
            push_stack.append(("insert", action[1], action[2], action[3]))
        else:
            return 0
        return 1
        
        

        

    def __str__(self):
        return self.buffer


s = Sequence()
rf = open("test.txt","r")
a = rf.read()
rf.close()
s.buffer = a
print(len(s.buffer))
st = time.time()
s.insert(222,"5")
en = time.time()
print(en-st)
#print(s)
