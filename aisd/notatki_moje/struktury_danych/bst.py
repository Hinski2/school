from typing import List

class Node: 
    def __init__(self, val: int, l = None, r = None) -> None:
        self.val: int = val
        self.l: Node | None = l 
        self.r: Node | None = r

class BST:
    def __init__(self) -> None:
        self.root: Node | None = None
    
    def insert(self, val: int) -> None:
        def _insert(node: Node | None, val: int) -> Node:
            if node == None:
                return Node(val)
            elif val < node.val:
                return Node(node.val, _insert(node.l, val), node.r)
            elif val > node.val:
                return Node(node.val, node.l, _insert(node.r, val))
            else:
                return node
        
        self.root = _insert(self.root, val)
    
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
    
    def remove(self, val) -> None:
        def _remove(node: Node | None, val: int) -> Node | None:
            if node == None:
                return None
            # we found the value to remove
            elif node.val == val:
                if node.l == None and node.r == None:       # no sons
                    return None
                elif node.l != None and node.r == None:     # only l son
                    return node.l
                elif node.l == None and node.r != None:     # only r son
                    return node.r
                elif node.l != None and node.r != None:     # two sons
                    # get smallest val in right subtree
                    mini = _get_smallest_val(node.r)
                    return Node(mini, node.l, _remove(node.r, mini))
                    
            elif val < node.val:
                return Node(node.val, _remove(node.l, val), node.r)
            elif val > node.val:
                return Node(node.val, node.l, _remove(node.r, val))
       
        def _get_smallest_val(node: Node) -> int:
            if node.l:
                return _get_smallest_val(node.l)
            else:
                return node.val
        
        self.root = _remove(self.root, val)
        
    def print(self) -> None:
        def _print(node: Node | None) -> str:
            if node == None:
                return "()"
            else:
                return f"[{node.val}, {_print(node.l)}, {_print(node.r)}]" 
            
        print(_print(self.root))

if __name__ == '__main__':
    bst = BST()
    bst.insert(2)
    bst.insert(1)
    bst.insert(3)
    bst.remove(2)
    bst.print()