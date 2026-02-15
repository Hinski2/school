from typing import List

def beta_encode(x: int) -> List[bool]:
    ans: List[bool] = []
    binary_representation: List[bool] = []
    
    while x:
        binary_representation.append(x & 1 == 1)
        x //= 2
    binary_representation.reverse()
    for _ in range(len(binary_representation)):
        ans.append(False)
        
    return ans + binary_representation