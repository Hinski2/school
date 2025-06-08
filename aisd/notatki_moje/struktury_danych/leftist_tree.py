class Node: 
    def __init__(self, val: int, l: "None|Node" = None, r: "Node|None" = None): 
        self.val = val 
        self.l = l
        self.r = r 
        self.h: int = 0
        self.update_h()
    
    def update_h(self) -> None:
        l_h = Node.get_save_h(self.l)
        r_h = Node.get_save_h(self.r)
        self.h = min(l_h, r_h) + 1
    
    def check_balance(self) -> bool:
        return Node.get_save_h(self.l) < Node.get_save_h(self.r)
    
    @staticmethod
    def get_save_h(node: 'None|Node') -> int:
        if node: 
            return node.h 
        else: 
            return 0
    
    @staticmethod
    def merge(a: 'Node|None', b: 'Node|None') -> 'Node|None':
        if a == None: 
            return b 
        if b == None:
            return a 
        
        # mnijsza val w a
        if a.val > b.val: a.val, b.val = b.val, a.val 
        
        # łacznie rekurencyjnie z prawą krawędzią 
        a.r = Node.merge(a.r, b)
        
        # ewentualny swap 
        a.update_h()
        if a.check_balance():
            a.l, a.r = a.r, a.l
            
        return a
        
class L_tree:
    def __init__(self):
        self.root: Node | None = None 
    
    def insert_val(self, val: int) -> None:
        tree = L_tree()
        tree.root = Node(val)
        self.insert_tree(tree)
        
    def insert_tree(self, tree: "L_tree") -> None:
        self.root = Node.merge(self.root, tree.root)
    
    def get_top(self) -> int|None:
        if self.root:
            return self.root.val 
        else: 
            return None
    
    def remove_top(self) -> int|None:
        if self.root == None:
            return None 
        
        top = self.get_top() 
        self.root = Node.merge(self.root.l, self.root.r)
        return top
    
    def print(self) -> None:
        def _print(node: Node | None):
            if node:
                return f"[{node.val}, {_print(node.l)}, {_print(node.r)}]"
            else:
                return "()"
        print(_print(self.root))
    
if __name__ == '__main__':
    tree = L_tree()
    tree.insert_val(5);
    tree.insert_val(7);
    tree.insert_val(3);
    tree.insert_val(6);
    tree.print()
        