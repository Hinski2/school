def gauss_elimination(matrix):
    """
    Przekształca macierz do postaci schodkowej Gaussa (row echelon form).
    matrix - lista list (macierz) o wymiarach m x n.
    """
    m = len(matrix)
    n = len(matrix[0])

    for k in range(min(m, n)):
        # Znalezienie wiersza z maksymalnym elementem w kolumnie k
        max_index = k
        max_value = abs(matrix[k][k])
        for i in range(k + 1, m):
            if abs(matrix[i][k]) > max_value:
                max_value = abs(matrix[i][k])
                max_index = i
        
        # Zamiana wierszy k i max_index
        if matrix[max_index][k] != 0:
            matrix[k], matrix[max_index] = matrix[max_index], matrix[k]
            
            # Zerowanie elementów poniżej pivotu
            for i in range(k + 1, m):
                if matrix[i][k] != 0:  # Unikamy dzielenia przez zero
                    f = matrix[i][k] / matrix[k][k]
                    for j in range(k, n):
                        matrix[i][j] -= f * matrix[k][j]

    return matrix

n, m = map(int, input("podaj rozmiar n i m\n").split())
matrix = []
print("podaj tą macierz")
for i in range(n):
    line = list(map(int, input().split()))
    matrix.append(line)
        
matrix = gauss_elimination(matrix) 
print(matrix)
        
