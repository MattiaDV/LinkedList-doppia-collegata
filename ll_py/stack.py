class Stack:
    def __init__(self):
        self.stack = []
        self.top = None
    def isEmpty(self):
        return len(self.stack) == 0
    def push(self, val: int):
        self.stack.append(val)
        self.top = len(self.stack) - 1
    def pop(self):
        if not self.isEmpty():
            el = self.stack[self.top]
            self.stack.pop()

            if self.top == 0:
                self.top = None
            else:
                self.top -= 1

            return el
    def peek(self):
        if not self.isEmpty():
            return self.stack[self.top]
        
s = Stack()
s.push(10)
s.push(20)
s.push(30)
s.pop()
s.push(40)
print(s.peek())