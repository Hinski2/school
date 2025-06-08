from typing import List 

def merge_sort(arr: List[int]) -> None:
    buff = [0 for _ in range(len(arr))]
    
    def _merge(a_l: int, a_r: int, b_l: int, b_r: int) -> None:
        arr_idx = a_l
        buff[a_l: b_r + 1] = arr[a_l: b_r + 1]
        
        while a_l <= a_r and b_l <= b_r: 
            if buff[a_l] < buff[b_l]:
                arr[arr_idx] = buff[a_l]
                a_l += 1
            else:
                arr[arr_idx] = buff[b_l]
                b_l += 1
            
            arr_idx += 1
        
        while a_l <= a_r:
            arr[arr_idx] = buff[a_l]
            a_l += 1 
            arr_idx += 1
        
        while b_l <= b_r: 
            arr[arr_idx] = buff[a_l]
            a_l += 1
            arr_idx += 1
            
    
    def _sort(l: int, r: int) -> None:
        if r - l + 1 == 1:
            return 
        elif r - l + 1 == 2: 
            if arr[l] > arr[r]:
                arr[l], arr[r] = arr[r], arr[l]
            return
        
        mid = (l + r) // 2
        
        _sort(l, mid)
        _sort(mid + 1, r)
        
        _merge(l, mid, mid + 1, r)
        
    
    _sort(0, len(arr) - 1)
    


if __name__ == "__main__":
    arr: List[int] = [1, 5, 5, 4, 2]
    merge_sort(arr)
    print(arr)