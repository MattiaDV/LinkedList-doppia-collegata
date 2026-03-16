class HashTable:
    def __init__(self):
        self.table = {}
    def insertValue(self, value):
        key = (value ** 2) % 10
        if key not in self.table or self.table[key] == None:
            self.table[key] = value
        else:
            i = key + 1
            k = 0
            while True:
                if i not in self.table or self.table[i] == None:
                    self.table[i] = value
                    return
                i += 1
                k += 1
        return None
    def seachValue(self, value):
        key = (value ** 2) % 10
        if self.table.get(key) == value:
            return key
        else:
            i = key + 1
            k = 0
            while k < len(self.table):
                if self.table.get(i) == value:
                    return i
                i += 1
                k += 1
        return None
    def delValue(self, value):
        key = (value ** 2) % 10
        if self.table.get(key) == value:
            self.table[key] = None
        else:
            i = key + 1
            k = 0
            while k < len(self.table):
                if self.table.get(i) == value:
                    self.table[i] = None
                    return
                i += 1
                k += 1
        return None
    def reorderTable(self):
        new_table = {}
        for key, val in self.table.items():
            if val != None:
                new_k = (val**2) % 10
                if new_k not in new_table or new_table[new_k] == None:
                    new_table[new_k] = val
                else:
                    i = key + 1
                    while True:
                        if i not in new_table or new_table[i] == None:
                            new_table[i] = val
                            break
                        i += 1
        self.table = new_table
        return

table = HashTable()
table.insertValue(10)
table.insertValue(11)
table.insertValue(12)
table.insertValue(13)
table.insertValue(14)
table.insertValue(44)
table.insertValue(22)
table.delValue(12)
table.reorderTable()
print(table.table)