import tkinter as tk

class HashTable:
    divisor = 1000
    def __init__(self):
        self.table = {}
    def insertWord(self, word, values, nome):
        nome.delete("1.0", "end")
        prime = 13
        hash_value = 5381
        for char in word:
            hash_value = (hash_value*prime+ord(char))
        hash_value = hash_value % self.divisor

        if hash_value not in self.table or self.table[hash_value] == None:
            self.table[hash_value] = word
        else:
            i = hash_value + 1
            while True:
                if i not in self.table or self.table[i] == None:
                    self.table[i] = word
                    break
                i += 1
        tutti = [v for v in self.table.values() if v is not None]
        values.config(text=", ".join(tutti))
    def delWord(self, word, values):
        prime = 13
        hash_value = 5381
        for char in word:
            hash_value = (hash_value*prime+ord(char))
        hash_value = hash_value % self.divisor

        if self.table.get(hash_value) == None:
            return None

        if self.table[hash_value] == word:
            self.table[hash_value] = None
        else:
            i = hash_value + 1
            while True:
                if self.table[i] == word:
                    self.table[i] = None
                    break
                i += 1
        tutti = [v for v in self.table.values() if v is not None]
        values.config(text=", ".join(tutti))
    def reorder(self):
        new_list = {}
        for key, val in self.table.items():
            if val != None:
                prime = 13
                hash_value = 5381
                for char in val:
                    hash_value = (hash_value*prime+ord(char))
                hash_value = hash_value % self.divisor
                key = hash_value
                
                new_list[key] = val
        self.table = new_list
    def searchValue(self, word):
        prime = 13
        hash_value = 5381
        for char in word:
            hash_value = (hash_value*prime+ord(char))
        hash_value = hash_value % self.divisor

        if hash_value not in self.table:
            return None

        if self.table[hash_value] == word:
            return hash_value
        
        i = hash_value + 1
        while True:
            if i not in self.table:
                return None
            if self.table[i] == word:
                return i
            i += 1 

window = tk.Tk()
window.geometry("600x400")
window.title("Rubrica")

table = HashTable()

nome = tk.Text(width=100, height=1)
nome.pack()
values = tk.Label(text="")
values.pack()
button = tk.Button(text="Salva in rubrica", command=lambda: table.insertWord(nome.get("1.0", "end-1c"), values, nome))
button.pack()

window.mainloop()