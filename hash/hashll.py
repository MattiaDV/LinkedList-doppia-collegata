class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class HashTable:
    def __init__(self):
        self.table = {}
    def insertValue(self, val):
        new_node = Node(val)
        key = (val ** 2) % 10
        if key not in self.table or self.table[key] == None:
            self.table[key] = new_node
        else:
            new_node.next = self.table[key]
            self.table[key] = new_node
    def searchValue(self, value):
        key = (value ** 2) % 10
        cur = self.table.get(key)
        while cur != None:
            if cur.value == value:
                return key
            cur = cur.next
        return None
    def delValue(self, val):
        key = (val ** 2) % 10
        cur = self.table.get(key)

        if cur == None:
            return None

        if self.table.get(key).value == val:
            self.table[key] = cur.next
            return
        
        prev = None
        while cur != None:
            if cur.value == val:
                prev.next = cur.next
                return
            prev = cur
            cur = cur.next
        return None
    def printTable(self):
        for key, val in self.table.items():
            row = f"{key}: "
            cur = val
            while cur != None:
                row += f"{cur.value} -> "
                cur = cur.next
            print(row)

table = HashTable()
table.insertValue(10)
table.insertValue(11)
table.insertValue(12)
table.insertValue(13)
table.insertValue(14)
table.insertValue(15)
table.insertValue(16)
table.insertValue(17)
table.insertValue(18)
table.delValue(12)
table.printTable()