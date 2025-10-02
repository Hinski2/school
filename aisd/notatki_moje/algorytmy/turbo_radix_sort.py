from typing import List 

def make_repr(x: int) -> List[int]:
    repr = []
    while x:
        repr.append(x % 10)
        x //= 10
        
    return repr[::-1]


def turbo_radix_sort(arr: List[List[int]]) -> None:
    max_len = max(len(repr) for repr in arr)
    repr_with_len: List[List[List[int]]] = [[] for _ in range(max_len)] # len --
    for repr in arr:
        repr_with_len[len(repr) - 1].append(repr)
        
        
    # remember nonempty buckets for each len
    non_empty_buckets = [set() for _ in range(max_len)]
    for repr in arr:
        for i, dig in enumerate(repr):
            non_empty_buckets[i].add(dig)
            
    non_empty_buckets = [sorted(s) for s in non_empty_buckets]
    
    arr[:] = []
    for l in range(max_len - 1, -1, -1): # len --
        # add new repr
        arr[:] = repr_with_len[l] + arr[:]

        # split into buckets
        buckets: List[List[List[int]]] = [[] for _ in range(10)]
        for repr in arr:
            buckets[repr[l]].append(repr)
        
        # recreate arr 
        arr[:] = []
        for digit in non_empty_buckets[l]:
            arr += buckets[digit]

if __name__ == '__main__':
    arr = [304854, 309843, 34, 93746, 3421039, 3330, 2, 5505555]
    arr = [make_repr(i) for i in arr]
    
    turbo_radix_sort(arr)
    print(arr)
    