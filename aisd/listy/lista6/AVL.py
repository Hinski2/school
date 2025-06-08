from typing import Tuple

class Node:
    def __init__(self, val: int, l: 'Node|None' = None, r: 'Node|None' = None) -> None:
        self.val = val
        self.l = l 
        self.r = r
        
        self.h: int = 1;
        self.update_h
        
        
    def update_h(self) -> None:
        self.h = max(Node.safe_high(self.l), Node.safe_high(self.r)) + 1
    
    def get_bf(self) -> int: 
        l = Node.safe_high(self.l)
        r = Node.safe_high(self.r)
        return l - r;
    
    @staticmethod
    def safe_high(node: 'Node | None') -> int:
        return node.h if node else 0 

    @staticmethod
    def rotate_left(B: 'Node') -> 'Node':
        if B.r == None:
            return B
        
        A: Node = B.r 
        B.r = A.l 
        A.l = B 
        
        A.update_h()
        B.update_h()
        
        return A
    
    @staticmethod 
    def rotate_right(A: 'Node') -> 'Node':
        if A.l == None:
            return A 
    
        B: Node = A.l 
        A.l = B.r 
        B.r = A 
        
        A.update_h() 
        B.update_h()
        
        return B
    
    @staticmethod
    def _rebalance(node: 'Node') -> 'Node':
        bf = node.get_bf()
        
        if bf > 1:
            if node.l and node.l.get_bf() < 0:
                node.l = Node.rotate_left(node.l)
            return Node.rotate_right(node)
        
        if bf < -1:
            if node.r and node.r.get_bf() > 0:
                node.r = Node.rotate_right(node.r)
            return Node.rotate_left(node)

        return node

    @staticmethod
    def _get_max(node: 'Node') -> Tuple['Node', 'Node|None']:
        if node.r == None:
            return (node, node.l) 
        
        max_node, node.r = Node._get_max(node.r)
        
        node.update_h()
        node = Node._rebalance(node)
        
        return max_node, node
        
    
    @staticmethod
    def merge2(a: 'Node|None', b: 'Node|None') -> 'Node|None':
        # a < b
        
        if a == None:
            return b 
        if b == None:
            return a 
        
        max_node, a = Node._get_max(a)
        
        max_node.l = a
        max_node.r = b
        
        max_node.update_h()
        return Node._rebalance(max_node)
    
    @staticmethod
    def merge3(a: 'Node|None', b: 'Node', c: 'Node|None') -> 'Node|None':
        # a < b < c. and b.l = b.r = none
        b.l = a;
        b.r = c;
        
        b.update_h()
        return Node._rebalance(b)
    
    @staticmethod
    def split(node: 'Node|None', k: int) -> Tuple['Node|None', 'Node|None']:
        if node == None:
            return (None, None)
        
        if node.val == k:
            return (node.l, Node.merge2(Node(node.val), node.r)) 
        elif node.val > k:
            le, geq = Node.split(node.l, k)
            return (le, Node.merge3(geq, Node(node.val), node.r))
        else:
            le, geq = Node.split(node.r, k)
            return (Node.merge3(node.l, Node(node.val), le), geq)
    
    @staticmethod 
    def insert(node: 'Node|None', val: int) -> 'Node':
        if node == None:
            return Node(val)
        elif val < node.val:
            node.l = Node.insert(node.l, val)
        else: 
            node.r = Node.insert(node.r, val)
        
        node.update_h()
        return Node._rebalance(node)
    
class AVL:
    def __init__(self, root: Node|None = None):
        self.root = root
    
    def split(self, k: int) -> Tuple['AVL', 'AVL']:
        le, geq = Node.split(self.root, k)
        return (AVL(le), AVL(geq))
    
    def insert(self, val: int) -> None:
        self.root = Node.insert(self.root, val)

    def print(self) -> None:
        def _print(node: Node | None) -> str:
            if node == None:
                return '()'
            else:
                return f'[{node.val}, {_print(node.l)}, {_print(node.r)}]' 
        
        print(_print(self.root))
    
if __name__ == '__main__':
    avl = AVL()
    avl.insert(5)
    avl.insert(7)
    avl.insert(8)
    avl.insert(10)
    avl.insert(4)
    avl.print()
    
    a, b = avl.split(7)
    a.print()
    b.print()
    
    