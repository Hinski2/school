from typing import List, Tuple

def quick_sort(arr: List[int]) -> None:
    def _quick_sort(l: int, r: int) -> None: # [l, r]
        if r - l <= 2:
            insert_sort(l, r)
        else: 
            arg_pivot = _partition(l, r)
            _quick_sort(l, arg_pivot - 1)
            _quick_sort(arg_pivot + 1, r)
            
    def partition(l: int, r: int) -> int:
        pivot, arg_pivot = get_pivot(l, r)
        
        # get pivot at the end
        arr[arg_pivot], arr[r] = arr[r], arr[arg_pivot]
        arg_pivot = r
        r -= 1
        
        while True: 
            while l <= r and arr[l] < pivot:
                l += 1
            while l <= r and arr[r] > pivot:
                r -= 1
            
            if l > r:
                break
            
            arr[l], arr[r] = arr[r], arr[l]
        
        # get back pivot        
        arr[arg_pivot], arr[l] = arr[l], arr[arg_pivot]
        return l
    
    def _partition(l: int, r: int) -> int:
        pivot, arg_pivot = get_pivot(l, r)
        
        # swap with last
        arr[r], arr[arg_pivot] = arr[arg_pivot], arr[r]
        i = l 
        
        for j in range(l, r):
            if arr[j] <= pivot:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1 
                
        arr[i], arr[r] = arr[r], arr[i]
        return i
    
    def insert_sort(l: int, r: int) -> None:
        for i in range(l + 1, r + 1):
            while i != l and arr[i - 1] > arr[i]:
                arr[i - 1], arr[i] = arr[i], arr[i - 1]
                i -= 1
    
    def get_pivot(l: int, r: int) -> Tuple[int, int]:
        mid = (l + r) // 2
        candidates = sorted([(arr[l], l), (arr[mid], mid), (arr[r], r)])
        return candidates[1]
    
    _quick_sort(0, len(arr) - 1)

if __name__ == '__main__':
    arr: List[int] = [1, 3, 5, 2, 3, 4, 7]
    quick_sort(arr)
    print(arr)
    