from typing import Union
opt = Union[None, 'Node']

class Node:
    def __init__(self, val: int, idx: int):
        self.val = val 
        self.l: opt = None
        self.r: opt = None
        
        self.shift: int = 0
        self.idx: int = idx
        
        self.h: int = 1
        self.sum_even: int = val if idx % 2 == 0 else 0  
        self.sum_odd: int = val if idx % 2 == 1 else 0
    
    #! update #########################
    def update_h(self) -> None:
        l_h = Node.get_h(self.l)
        r_h = Node.get_h(self.r)
        self.h = max(l_h, r_h) + 1 
    
    def update_sum(self) -> None:
        Node.lazy_update(self.l) 
        Node.lazy_update(self.r) 
        
        l_sum_even = Node.get_sum_even(self.l)
        r_sum_even = Node.get_sum_even(self.r)
        self.sum_even = l_sum_even + r_sum_even
        if self.idx % 2 == 0: self.sum_even += self.val
        
        l_sum_odd = Node.get_sum_odd(self.l) 
        r_sum_odd = Node.get_sum_odd(self.r) 
        self.sum_odd = l_sum_odd + r_sum_odd
        if self.idx % 2 == 1: self.sum_odd += self.val
    
    @staticmethod 
    def lazy_update(node: opt) -> None: 
        if node == None or node.shift == 0:
            return 
        
        # swap 
        node.idx += node.shift
        
        if node.shift % 2 == 1:
            node.sum_even, node.sum_odd = node.sum_odd, node.sum_even 
        
        # lazy propagate 
        if node.l:
            node.l.shift += node.shift
            
        if node.r:
            node.r.shift += node.shift
            
        node.shift = 0
    
    #! rotatnions ######################
    @staticmethod
    def rotate_right(A: 'Node') -> 'Node':
        if A.l == None:
            return A 
    
        B: Node = A.l 
        A.l = B.r 
        B.r = A 
        
        A.update_h(); A.update_sum()
        B.update_h(); B.update_sum()
        
        return B
    
    @staticmethod
    def rotate_left(B: 'Node') -> 'Node':
        if B.r == None:
            return B
        
        A: Node = B.r 
        B.r = A.l 
        A.l = B 
        
        A.update_h(); A.update_sum()
        B.update_h(); B.update_sum()
        
        return A
    
    #! rebalance #####################
    def get_bf(self) -> int:
        l_h = Node.get_h(self.l)
        r_h = Node.get_h(self.r)
        return l_h - r_h
    
    @staticmethod 
    def rebalance(node: 'Node') -> 'Node':
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
   
    #! getters #######################
    @staticmethod
    def get_h(node: opt) -> int:
        return node.h if node else 0  
    
    @staticmethod 
    def get_sum_even(node: opt) -> int:
        return node.sum_even if node else 0
    
    @staticmethod 
    def get_sum_odd(node: opt) -> int:
        return node.sum_odd if node else 0
    
class AVL:
    def __init__(self, root: opt = None):
        self.root = root
        
    def insert(self, idx: int, val: int) -> None:
        def _insert(node: opt, idx: int) -> Node:
            Node.lazy_update(node)
            
            if node == None:
                return Node(val, idx)
            
            elif idx <= node.idx:
                # add to left son 
                node.l = _insert(node.l, idx)
                
                # update everyfing in right
                if node.r:
                    node.r.shift += 1
                    
                # update our idx
                node.idx += 1
                    
            else:
                node.r = _insert(node.r, idx)
            
            #update 
            node.update_sum()
            node.update_h()
             
            return Node.rebalance(node)
        
        self.root = _insert(self.root, idx)
    
    def delete(self, idx: int) -> None:
        def _get_min(node: Node) -> Node:
            Node.lazy_update(node)
             
            if node.l:
                return _get_min(node.l)
            else:
                return node
        
        def _delete(node: opt, idx) -> opt:
            Node.lazy_update(node)
            
            if node == None:
                return None
            
            elif idx == node.idx: # we have found our target
                Node.lazy_update(node.l)
                Node.lazy_update(node.r) 
                
                if node.l == None and node.r == None:
                    return None 
                elif node.l == None and node.r:
                    node.r.shift -= 1
                    return node.r 
                elif node.r == None: 
                    return node.l
                else: # we have 2 sons
                    min_node = _get_min(node.r)
                    node.val = min_node.val 
                    node.r = _delete(node.r, min_node.idx)
                
            elif node.l and idx < node.idx:
                node.l = _delete(node.l, idx) 
                
                # update everythin in right 
                if node.r:
                    node.r.shift -= 1
                
                # update our idx
                node.idx -= 1
                 
            elif node.r:
                node.r = _delete(node.r, idx)
                
            #update 
            node.update_sum()
            node.update_h()
            
            return Node.rebalance(node)
        
        #invoke fun 
        self.root = _delete(self.root, idx)
    
    def find(self, idx: int) -> int:
        def _find(node: Node, idx: int) -> int:
            if idx == node.idx: # idx of our node
                return node.val 
            elif node.l and idx < node.idx:
                return _find(node.l, idx)
            elif node.r:
                return _find(node.r, idx) # idx -= l tree + we 
            
            return -1 # invalid input
        
        # invoke fun
        if self.root == None:
            return 0 
        else: 
            return _find(self.root, idx)
    
    def sum_of_even(self) -> int:
        if self.root == None:
            return 0 
        
        Node.lazy_update(self.root)
        return self.root.sum_even
        
    def sum_of_odd(self) -> int:
        if self.root == None:
            return 0 
        
        Node.lazy_update(self.root)
        return self.root.sum_odd
    
    def print(self):
        def _print(node: Node | None) -> str:
            if node == None:
                return '()'
            else:
                return f'[{node.val}, {_print(node.l)}, {_print(node.r)}]' 
        
        print(_print(self.root))
         
if __name__ == '__main__':
    avl = AVL()
    avl.insert(1, 4)
    avl.insert(2, 3)
    avl.delete(1)
     
    print("even", avl.sum_of_even())
    print("odd", avl.sum_of_odd())