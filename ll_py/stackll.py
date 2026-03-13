import random

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        self.head = None

    def push(self, val: int):
        n = Node(val)
        n.next = self.head
        self.head = n
    
    def pop(self):
        if self.head is not None:
            n = self.head
            self.head = self.head.next
            return n.data
        
    def peek(self):
        if self.head is not None:
            return self.head.data
        
s = Stack()

for _ in range(1000000):
    s.push(random.randint(1, 10000))

s.pop()
print(s.peek())