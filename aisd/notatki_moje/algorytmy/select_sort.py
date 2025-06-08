from typing import List, Tuple

def select_sort(arr: List[int]) -> List[int]:

    def get_min(arr: List[int]): # (min, argmin)
        mini: None|int = None 
        argmini: int = 0
        
        for idx, val in enumerate(arr):
            if mini == None or val < mini:
                mini = val 
                argmini = idx 
        
        return (mini, argmini)
    
    for i in range(len(arr)):
        _, argmini = get_min(arr[i:])
        arr[i], arr[argmini + i] = arr[argmini + i], arr[i]
        
    return arr
                


if __name__ == '__main__':
    data: List[int] = [1, 3, 2, 5, 7, 6]
    print(select_sort(data))
    