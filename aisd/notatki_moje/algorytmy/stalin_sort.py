from typing import List, Tuple

def stalin_sort(arr: List[int]): 
    ans: List[int] = []
    for u in arr:
        if len(ans) == 0 or ans[-1] <= u:
            ans.append(u)
    return ans

if __name__ == '__main__':
    arr: List[int] = [1, 4, 5, 3, 2, 8, 9]
    print(stalin_sort(arr))