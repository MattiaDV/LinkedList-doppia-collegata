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
table.insertValue(1)
table.insertValue(2)
table.insertValue(3)
table.insertValue(4)
table.insertValue(5)
table.insertValue(6)
table.insertValue(7)
table.insertValue(8)
table.insertValue(9)
table.insertValue(10)
table.insertValue(11)
table.insertValue(12)
table.insertValue(13)
table.insertValue(14)
table.insertValue(15)
table.insertValue(16)
table.insertValue(17)
table.insertValue(18)
table.insertValue(19)
table.insertValue(20)
table.insertValue(21)
table.insertValue(22)
table.insertValue(23)
table.insertValue(24)
table.insertValue(25)
table.insertValue(26)
table.insertValue(27)
table.insertValue(28)
table.insertValue(29)
table.insertValue(30)
table.delValue(12)
table.printTable()