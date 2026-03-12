class Node:
    def __init__(self, valore):
        self.valore = valore
        self.next = None

class linkedList:
    def __init__(self):
        self.head = None

    def addNode(self, valore):
        new_node = Node(valore)
        new_node.next = None
        if self.head == None:
            self.head = new_node
            print("Valore aggiunto con successo!\n")
            return
        
        cur = self.head
        while cur.next != None:
            cur = cur.next
        
        cur.next = new_node
        print("Valore aggiunto con successo!\n")

    def delNode(self, valore):
        if self.head is None:
            print("La lista è vuota!\n")
            return
        
        if self.head.valore == valore:
            self.head = self.head.next
            print("Valore eliminato con successo!\n")
            return 
        
        cur = self.head
        prev = None

        while cur is not None:
            if cur.valore == valore:
                print("Valore eliminato con successo!\n")
                prev.next = cur.next
                return
            
            prev = cur
            cur = cur.next

        print("Nessun valore matcha!\n")

    def viewNormal(self):
        cur = self.head
        while cur != None:
            print(f"Value: {cur.valore}")
            print(f"    |")
            print(f"   \|/")
            cur = cur.next

    def viewNode(self):
        cur = self.head
        while cur != None:
            print(f"Value: {cur.valore}\nNext: {cur.next}\n")
            cur = cur.next

    def somma(self):
        s = 0
        cur = self.head
        while cur is not None:
            s = s + cur.valore
            cur = cur.next

        return s

def main():
    lista = linkedList()
    while True:
        print("\n\n0) Esci\n1) Aggiungi nodo\n2) Guarda nodi con indirizzo\n3) Guarda nodi senza indirizzo\n4) Elimina valore\n5) Somma dei valori")
        scelta = int(input("Scegli: "))
        print("\n")

        match(scelta):
            case 0:
                print("\nCiao ciao!")
                return 0
            case 1:
                valore = int(input("Inserire valore da aggiungere: "))
                lista.addNode(valore)
            case 2:
                lista.viewNode()
            case 3:
                lista.viewNormal()
            case 4:
                val = int(input("Inserire valore da eliminare: "))
                lista.delNode(val)
            case 5:
                a = lista.somma()
                print(f"Somma di tutti i valori: {a}\n")
            case _:
                print("Inserisci un valore valido!\n")

if __name__ == "__main__":
    main()