def a(x, y, z): return (1 * x + 3 * y + 5 * z) % 7 == 1 % 7
def b(x, y, z): return (2 * x + 6 * y + 3 * z) % 7 == 2 % 7
def c(x, y, z): return (6 * x + 4 * y + 2 * z) % 7 == -1 % 7

ans = 0
for i in range(7):
    for j in range(7):
        for k in range(7):
            ans += a(i, j, k) + b(i, j, k) + c(i, j, k) == 3
            
print(ans)