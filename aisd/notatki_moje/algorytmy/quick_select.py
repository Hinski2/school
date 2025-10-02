from typing import List, Tuple

def get_kth(arr: List[int], k: int) -> int:
    
    def get_pivot(l: int, r: int) -> Tuple[int, int]: # [pivot, pivot_pos]
        mid = (l + r) // 2
        return sorted([(arr[l], l), (arr[mid], mid), (arr[r], r)])[1]
    
    def partition(l: int, r: int) -> Tuple[int, int]: # [pivot, pivot_pos]
        pivot, pivot_pos = get_pivot(l, r)
        arr[pivot_pos], arr[r] = arr[r], arr[pivot_pos]
        
        i: int = l 
        for j in range(l, r):
            if arr[j] <= pivot:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
        
        arr[i], arr[r] = arr[r], arr[i]
        return pivot, i         
    
    def base_case(l: int, r: int) -> int:
        return sorted(arr[l: r + 1])[k - l]
    
    l, r = 0, len(arr) - 1
    while True: 
        if r - l + 1 <= 5:
            return base_case(l, r)
        
        pivot, pivot_pos = partition(l, r)
        if pivot_pos == k:
            return pivot 
        elif pivot_pos > k:
            r = pivot_pos - 1
        else: 
            l = pivot_pos + 1

if __name__ == '__main__':
    arr: List[int] = [1, 4, 5, 3, 2, 8, 9]
    for i in range(len(arr)):
        print(get_kth(arr, i))