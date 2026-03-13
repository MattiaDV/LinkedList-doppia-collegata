class Queue:
    def __init__(self):
        self.queue = []
    def isEmpty(self):
        return len(self.queue) == 0
    def enqueue(self, item):
        self.queue.append(item)
    def dequeue(self):
        if not self.isEmpty():
            return self.queue.pop(0)
        else:
            raise IndexError("Queue is empty")
    def peek(self):
        if not self.isEmpty():
            return self.queue[0]
        else:
            raise IndexError("Queue is empty")
    def reverse(self):
        if not self.isEmpty():
            new_q = Queue()
            idx = len(self.queue) - 1
            while idx >= 0:
                temp = self.queue[idx]
                new_q.enqueue(temp)
                idx -= 1
            self.queue = new_q.queue

q = Queue()    
i = 0
messaggi = [1, 4, 1, 2, 1, 2, 3, 1, 1, 2]

while i < len(messaggi):
    q.enqueue(messaggi[i])
    i += 1

q.reverse()

i = 0
while i < len(messaggi):
    val = q.peek()

    if val == 1:
        print("Vale 1!")
    elif val == 2:
        print("Vale 2!")
    else:
        print(f"VALUE ERROR, valore '{val}' alla posizione: {i + 1}")

    q.dequeue()
    i += 1