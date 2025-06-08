from typing import List, Tuple

def insert_sort(arr: List[int]) -> List[int]:
    for idx in range(1, len(arr)):
        while idx - 1 >= 0 and arr[idx - 1] > arr[idx]:
            arr[idx - 1], arr[idx] = arr[idx], arr[idx - 1]
            
    return arr

if __name__ == '__main__':
    data: List[int] = [1, 3, 2, 5, 7, 6]
    print(insert_sort(data))
    