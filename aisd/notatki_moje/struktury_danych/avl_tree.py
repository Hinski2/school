class Node:
    def __init__(self, val: int, l = None, r = None) -> None:
        self.val = val
        self.l: Node | None = l 
        self.r: Node | None = r
        self.h = 1;
     
    def _safe_high(self, node: 'Node | None') -> int:
        return node.h if node else 0 
        
    def compute_new_h(self) -> int:
        return max(self._safe_high(self.l), self._safe_high(self.r)) + 1
    
    def get_bf(self) -> int: 
        l = self._safe_high(self.l)
        r = self._safe_high(self.r)
        return r - l
        
class AVL:
    def __init__(self):
        self.root: Node | None = None
        
    def _rotate_right(self, A: Node) -> Node:
        if A.l == None:
            return A
        
        B: Node = A.l 
        A.l = B.r
        B.r = A
        
        A.h = A.compute_new_h()
        B.h = B.compute_new_h()
        
        return B
    
    def _rotate_left(self, B: Node) -> Node:
        if B.r == None:
            return B
        
        A: Node = B.r 
        B.r = A.l 
        A.l = B 
        
        A.h = A.compute_new_h() 
        B.h = B.compute_new_h()
        
        return A
        
    def insert(self, val: int) -> None:
        def _insert(node: Node | None) -> Node:
            # first we insert
            if node == None:
                return Node(val)
            elif val < node.val:
                node.l = _insert(node.l)
            else: 
                node.r = _insert(node.r)
            
            # make perfect balance     
            node.h = node.compute_new_h()
            return _update_balance(node)
            
        def _update_balance(node) -> Node:
            bf = node.get_bf()
            
            # we have to change sth
            if bf > 1 and val < node.l.val:
                return self._rotate_right(node)
            
            elif bf < -1 and val > node.r.val:
                return self._rotate_left(node)
            
            elif bf > 1 and val > node.l.val:
                node.l = self._rotate_left(node.l)
                return self._rotate_right(node)
            
            elif bf < -1 and val < node.l.val:
                node.r = self._rotate_right(node.r)
                return self._rotate_left(node)
            
            # everything ok 
            return node
        
        if not self.contains(val):
            self.root = _insert(self.root)
    
    def contains(self, val: int) -> bool:
        def _contains(node: Node | None, val: int) -> bool:
            if node == None:
                return False
            elif node.val == val:
                return True 
            elif val < node.val:
                return _contains(node.l, val)   
            elif val > node.val:
                return _contains(node.r, val)
            else:
                return False
            
        return _contains(self.root, val)
    
    def delete(self, val: int) -> None:
        pass
    
    def print(self) -> None:
        def _print(node: Node | None) -> str:
            if node == None:
                return '()'
            else:
                return f'[{node.val}, {_print(node.l)}, {_print(node.r)}]' 
    
if __name__ == '__main__':
    avl = AVL()
    