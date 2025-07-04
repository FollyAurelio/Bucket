import time
class Sequence:

    def __init__(self):
        
        self.buffer = []
        self.gap_ptr = 0
        self.gap_length = 0
        self.buf_length = 0
        self.resize_gap(20)

    def move_gap(self,index):
        if index <= self.gap_ptr:
            for i in range(self.gap_ptr-1, index-1, -1):
                self.buffer[i + self.gap_length] = self.buffer[i]
        else:
            for i in range(self.gap_ptr+self.gap_length,self.gap_ptr+self.gap_length+index):
                self.buffer[i - self.gap_length] = self.buffer[i]

        for i in range(self.gap_length):
            self.buffer[index + i] = " "
        self.gap_ptr = index


    def resize_gap(self, size):
        temp_ptr = self.gap_ptr
        self.gap_ptr = self.buf_length
        self.buffer = self.buffer + [" "] * size
        self.gap_length = size
        self.buf_length += size
        self.move_gap(temp_ptr)

    def insert(self, index, text):
        length = len(text)
        if index != self.gap_ptr:
            self.move_gap(index)
        for i in range(length):
            if self.gap_length <= 0:
                self.resize_gap(20)
            self.buffer[self.gap_ptr] = text[i]
            self.gap_ptr += 1
            self.gap_length -= 1

    def erase(self,index, length):
        if index != self.gap_ptr:
            self.move_gap(index)
        self.gap_length += length


    def __str__(self):
        x = "" 
        for i in range(self.gap_ptr):
            x += self.buffer[i]
        for i in range(self.gap_ptr + self.gap_length, len(self.buffer)):
            x += self.buffer[i]
        return x


    def print(self):
        return "".join(self.buffer)
        


s = Sequence()
s.insert(0,"asdfb")
s.insert(5,"1111")
#s.erase(3,6)
print(s.gap_length)
s.insert(9,"1111")
"""
rf = open("test.txt","r")
a = rf.read()
rf.close()
s.insert(0,a)
#print(a)
print(len(s.buffer))
st = time.time()
s.insert(33000, "me and you")
en = time.time()
print(en-st)
"""
print(s)
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
        
        print(s)
if __name__ == "__main__":
    main()

