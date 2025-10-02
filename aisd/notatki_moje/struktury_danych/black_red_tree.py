from typing import List, Tuple, Union
opt = Union[None, 'Node']
black, red = range(1) # enum

class Node:
    def __init__(self, val: int, parent: opt = None, color: int = red) -> None:
       self.l: opt = None
       self.r: opt = None
       self.parent: opt = parent
       
       self._color = color
       self.val = val
       
    #! utils 
    @staticmethod
    def xor_color(node: opt) -> None:
        if node == None:
            return
        node._color = black if node._color == red else red
       
    #! getters
    @staticmethod
    def get_color(node: opt) -> int:
        if node == None:
            return black 
        return node._color
   
    #! rotations
    def rotate_right(self) -> None:
        A: opt = self.l
        if A == None:
            return
        
        self.l = A.r 
        A.r = self
        
        if A.r: 
            A.r.parent = self
            
        if self.parent:
            if self.parent.l == self:
                self.parent.l = A 
            else:
                self.parent.r = A
            
        A.parent = self.parent
        self.parent = A 
        
        A.r = self 
    
    def rotate_left(self) -> None:
        B: opt = self.r 
        if B == None:
            return
        
        self.r = B.l 
        B.l = self
        
        if B.l:
            B.l.parent = self
            
        if self.parent:
            if self == self.parent.l:
                self.parent.l = B 
            else: 
                self.parent.r = B
        
        B.parent = self.parent 
        self.parent = B 
        
        B.l = self
   
    @staticmethod 
    def get_uncle(node: 'Node') -> opt:
        parent: opt = node.parent 
        if parent == None:
            return None
        
        grandparent: opt = parent.parent
        if grandparent == None: 
            return None
        
        if grandparent.l == parent:
            return grandparent.r 
        else:
            return grandparent.l
    
    @staticmethod 
    def get_grandparent(node: 'Node') -> opt:
        parent: opt = node.parent 
        if parent == None:
            return None
        
        grandparent: opt = parent.parent
        return grandparent
        
    
    @staticmethod
    def update_balance(node: 'Node') -> 'Node':
        parent: opt = node.parent
        uncle: opt = Node.get_uncle(node)
        grandparent: opt = Node.get_grandparent(node)
        
        # if it's a root
        if parent == None:
            node._color = black
            return node
        
        # if we don't have grandparent
        if grandparent == None:
            return node
        
        if Node.get_color(uncle) == red: 
            Node.xor_color(parent)
            Node.xor_color(uncle)
            Node.xor_color(grandparent)
            return node
        
        if grandparent.r == parent:
            if node == parent.l: # zigzag
                parent.rotate_right()
            grandparent.rotate_left()
        else: 
            if node == parent.r: #zigzag
                parent.rotate_left()
            grandparent.rotate_right()
       
        return node 
        
class Red_black_tree:
    
    def __init__(self) -> None:
        self.root = None
    
    def insert(self, val: int) -> None:
        def _insert(node: opt, parent: opt) -> Node:
            if node == None: 
                return Node(val, parent)
            elif val < node.val:
                node.l = _insert(node.l, node)
            else:
                node.r = _insert(node.r, node)
                
            return Node.update_balance(node) 
        
        self.root = _insert(self.root, None)
        
    def contains(self, val: int) -> bool:
        def _contains(node: opt) -> bool: 
            if node == None:
                return False
            elif node.val == val:
                return True 
            elif val < node.val: 
                return _contains(node.l)
            else:
                return _contains(node.r)
            
        return _contains(self.root) 
    
if __name__ == '__main__':
    rbt = Red_black_tree()
    
