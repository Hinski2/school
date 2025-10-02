from typing import List, Tuple

def bucket_sort(arr: List[float]) -> List[float]:
    def _insert_to_bucket(val: float) -> None:
        idx = int(val * no_buckets)
        buckets[idx].append(val)
        
    def _inset_to_bucket_range(mini: int, maxi: int, val: int) -> None:
        idx = int((val - mini) / (maxi - val + .000001)) * no_buckets # we must add some epsilon
        buckets[idx].append(val)
    
    no_buckets = len(arr) // 2
    buckets: List[List[float]] = [[] for _ in range(no_buckets)]
    
    for u in arr: 
        _insert_to_bucket(u)
        
    ans: List[float] = []
    for bucket in buckets: 
        bucket.sort()
        ans += bucket
        
    return ans
        
    

if __name__ == '__main__':
    arr: List[float] = [0.4, 0.23, 0.1, 0.78, 0.33, 0.37, 0.41]
    arr = bucket_sort(arr)
    print(arr)
     