from typing import List
import random
import math

def lazy_select(arr: List[int]) -> int: 
    n = len(arr)
    k: int = math.ceil(n ** (3/4))
    
    while True:

        random_probe = sorted(random.choices(arr, k=k))
        d: int = random_probe[max(0,     k // 2 - int(math.sqrt(n)))]
        u: int = random_probe[min(k - 1, k // 2 + int(math.sqrt(n)))]

        # make corridor
        corridor: List[int] = [x for x in arr if d <= x <= u]
        below = len([x for x in arr if x < d])
        above = len([x for x in arr if x > u])

        # corridor too small 
        if above > n // 2 or below > n // 2:
            continue # fail

        if len(corridor) <= 4*k:
            corridor.sort()
            return corridor[(n - 1) // 2 - below]
        else:  # corridor too big
            continue # fail
    
if __name__ == '__main__':
    arr: List[int] = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    print(lazy_select(arr))
    
    arr: List[int] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    print(lazy_select(arr))
    
    arr: List[int] = [1, 2]
    print(lazy_select(arr))
    
    arr: List[int] = [1, 2, 3, 4]
    print(lazy_select(arr))
    
    
