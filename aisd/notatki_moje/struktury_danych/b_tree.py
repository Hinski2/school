from typing import List, Tuple 
import bisect

class Node: 
    def __init__(self) -> None:
        self.keys: List[int] = [] 
        self.children: List['Node'] = []
        
    def add_key(self, key: int) -> None: # insert sort
        idx = bisect.bisect_left(self.keys, key)
        self.keys.index(idx, key)
            
    def is_leaf(self) -> bool:
        return not self.children

class B_tree:
    def __init__(self, b: int) -> None:
        self.b = b 
        
        self.root: Node = Node()
    
    def insert(self, val: int) -> None:
        def _split(node: Node) -> Tuple[List[int], int, List[int], List[Node], List[Node]]:
            t = self.b
            
            # keys 
            down: List[int] = node.keys[: t - 1]
            mid: int = node.keys[t - 1]
            up: List[int] = node.keys[t:]
            
            # children
            if node.is_leaf():
                left_chidren = []
                right_children = []
            else:
                left_chidren = node.children[:t] 
                right_children = node.children[t:]

            
            return down, mid, up, left_chidren, right_children
        
        def _handle_overflow(node: Node, parent: Node|None) -> None:
            down, mid, up, left_children, right_children = _split(node)
            
            # handle left side 
            node.keys = down 
            node.children = left_children
            
            # handle right side 
            node2 = Node() 
            node2.keys = up 
            node2.children = right_children
            
            # handle mid
            if parent is None:
                new_root = Node() 
                new_root.keys = [mid]
                new_root.children = [node, node2]
                self.root = new_root
            else: 
                idx = bisect.bisect_left(parent.keys, mid) # finds place for mid
                parent.keys.insert(idx, mid)
                parent.children.insert(idx + 1, node2)
        
        def _insert(node: Node, parent: Node|None) -> None:
            if node.is_leaf(): 
                node.add_key(val)
            else:
                for i, key in enumerate(node.keys):
                    if val < key:
                        _insert(node.children[i], node)
                        break
                else:
                    _insert(node.children[-1], node)
                    
            # after insertion we must check if we don't have too much children
            if len(node.keys) > 2*self.b - 1:
                _handle_overflow(node, parent)
       
        _insert(self.root, None)
        
    def delete(self, val: int) -> None:
        def _handle_underflow(node: Node, parent: Node|None) -> None:
            if node.is_leaf():
                # we try to still key and children from our left sibling
                
            else:
                pass 
        
        def _delete(node: Node, parent: Node|None) -> None:
            if node.is_leaf():
                node.keys.remove(val) # we asume we don't try tro remove nonexisting key
            else:
                for i, key in enumerate(node.keys):
                    if key == val:
                        pass 
                    elif val < key:
                        _delete(node.children[i], node)
                        break 
                else:
                    _delete(node.children[-1], node)
                    
            # check if we have enough children
            if len(node.keys) < self.b - 1:
                _handle_underflow(node, parent)
        
        _delete(self.root, None)
    
    def contains(self, val: int) -> bool:
        def _contains(node: Node) -> bool:
            if node.is_leaf(): 
                return val in node.keys
            
            for i, key in enumerate(node.keys):
                if val == key:
                    return True 
                elif val < key:
                    return _contains(node.children[i])
            else:
                return _contains(node.children[-1])
            
        return _contains(self.root)

if __name__ == '__main__':
    bt = B_tree(3)