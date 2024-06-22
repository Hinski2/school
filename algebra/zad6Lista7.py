def process(x, n):
    l = []
    for i in range(n):
       l.append(int(x & (1 << i) != 0))
       
    return l

def zamien(v, i):
    v[i] ^= 1
    if i != 0: v[i - 1] ^= 1
    if i + 1 != len(v): v[i + 1] ^= 1
    
    
for n in range(1, 20): 
    print(n, end=' ')
    opt = []
    for i in range(1, 1 << n):
        opt.append(process(i, n))
    
    if n == 5:
        pass
    for o in opt:
        q = [o]
        s = set()
        nice = False
        while q:
            v = q.pop()
            if tuple(v) in s: continue
            s.add(tuple(v))
            for i in range(n):
                zamien(v, i)
                if all(u == 0 for u in v):
                    nice = True
                    break
                if not tuple(v) in s:
                    q.append(v.copy())
                    zamien(v, i)
        if not nice:
            print("NOT NICE")
            break
    else:
        print("NICE")
    

