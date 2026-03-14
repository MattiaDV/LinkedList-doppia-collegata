class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

class Tree:
    def __init__(self, root):
        self.root = Node(root)
        self.queue = []
    def add_node(self, nodo: Node, val : int):
        new_node = Node(val)
        if val > nodo.val:
            if nodo.right == None:
                nodo.right = new_node
            else:
                self.add_node(nodo.right, val)
        elif val < nodo.val:
            if nodo.left == None:
                nodo.left = new_node
            else:
                self.add_node(nodo.left, val)
    def clear_tree(self):
        self.root = None
        self.queue = None
    def view_node(self, nodo: Node):
        if nodo == None:
            return None
        if nodo != None:
            self.view_node(nodo.left)
            self.queue.append(nodo.val)
            print(str(nodo.val) + " ")
            self.view_node(nodo.right)
        else:
            return None
    def build_balanced_bst(self, arr):
        if not arr:
            return None
        mid = len(arr) // 2
        root = Node(arr[mid])
        root.left = self.build_balanced_bst(arr[:mid])
        root.right = self.build_balanced_bst(arr[mid+1:])
        return root

tree = Tree(10)

tree.add_node(tree.root, 5)
tree.add_node(tree.root, 20)
tree.add_node(tree.root, 3)
tree.add_node(tree.root, 7)
tree.add_node(tree.root, 4)
tree.add_node(tree.root, 9)
tree.add_node(tree.root, 25)
tree.add_node(tree.root, 16)
tree.add_node(tree.root, 30)
tree.add_node(tree.root, 12)
tree.add_node(tree.root, 15)

tree.view_node(tree.root)
q = tree.queue
tree.queue = []

tree.root = tree.build_balanced_bst(q)
tree.view_node(tree.root)