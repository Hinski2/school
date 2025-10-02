from typing import List, Tuple

def get_median(arr: List[int]) -> int:
    
    def pseudo_median(l: int, r: int) -> int:
        v: List[int] = [arr[i] for i in range(l, r + 1)] 
        while len(v) > 5:
            chunks = [v[i: i + 5] for i in range(0, len(v), 5)]
            v = [] 
            
            for chunk in chunks: 
                v.append(sorted(chunk)[len(chunk) // 2])
        
        return sorted(v)[len(v) // 2]
    
    def get_pivot(l: int, r: int) -> Tuple[int, int]: # [pivot, pivot_pos]
        p_median = pseudo_median(l, r)
        return p_median, arr[l:r+1].index(p_median) + l 
    
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
    
    l, r = 0, len(arr) - 1
    k = (len(arr) - 1) // 2
    
    while True: 
        if r - l + 1 <= 5:
            return sorted(arr[l: r + 1])[k - l]
        
        pivot, pivot_pos = partition(l, r)
        if pivot_pos == k:
            return pivot 
        elif pivot_pos > k:
            r = pivot_pos - 1
        else: 
            l = pivot_pos + 1

if __name__ == '__main__':
    arr: List[int] = [1, 4, 5, 3, 2, 8, 9]
    print(get_median(arr))
    
    arr: List[int] = [1, 2, 3]
    print(get_median(arr))
    
    arr: List[int] = [1, 2, 3, 4, 5, 6]
    print(get_median(arr))