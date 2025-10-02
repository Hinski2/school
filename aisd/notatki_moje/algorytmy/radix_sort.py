from typing import List, Tuple

def no_dig(x: int) -> int:
    ans = 0
    while x: 
        ans += 1
        x //= 10
        
    return ans

def represent_with_len(x: int, target_len: int) -> List[int]:
    l = 0
    ans = []
    while x:
        ans.append(x % 10)
        x //= 10
        l += 1
        
    for _ in range(l, target_len):
        ans.append(0)
        
    return ans[::-1]

def radix_sort(arr: List[List[int]]) -> None:
    max_len = len(arr[0])
    
    for i in range(max_len - 1, -1, -1): 
        buckets = [[] for _ in range(10)]
        
        for repr in arr:
            buckets[repr[i]].append(repr)
            
        arr[:] = []
        for bucket in buckets:
            arr += bucket

if __name__ == '__main__':
    arr = [53000989, 33433, 32342, 131, 45, 3, 4120573]
    max_len = max(no_dig(i) for i in arr) 
    arr = [represent_with_len(i, max_len) for i in arr]
    
    radix_sort(arr)
    print(arr) 
    