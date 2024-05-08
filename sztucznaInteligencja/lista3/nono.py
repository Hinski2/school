from queue import PriorityQueue
from itertools import combinations
from random import shuffle

yes, idk, no = [1, 0, -1] # pseudo enum
row_enum, col_enum = range(2) #psudo enum
    
def make_line_poss(empty_no, blocks_no, ones):
    line_poss = []
    for p in combinations(range(empty_no + blocks_no), blocks_no):
        selected = [no] * (empty_no + blocks_no)
        idx = 0
        for val in p:
            selected[val] = idx
            idx += 1
        
        res = [ones[val] + [-1] if val > -1 else [-1] for val in selected]
        res = [item for sublist in res for item in sublist][:-1]
        line_poss.append(res)
    return line_poss

def make_poss(lines, n):
    lines_poss = []
    for line in lines:
        blocks_no = len(line)
        empty_no = n - sum(line) - blocks_no + 1
        ones = [[1] * pixel for pixel in line]
        line_poss = make_line_poss(empty_no, blocks_no, ones)
        lines_poss.append(line_poss)
    
    return lines_poss

# wybiera idx lini które jeszcze nie zostały rozwiązane całkowicie
def select_not_solved(poss, done, enum):
    s = [len(i) for i in poss]
    return [(liczba_mozliwosci, i, enum) for i, liczba_mozliwosci in enumerate(s) if done[i] == 0]

def get_same_pixels(poss):
    poss_no = len(poss)
    if poss_no == 0: return []
    
    line_len = len(poss[0])
    sum = [0] * line_len
    for p in poss:
        for i in range(line_len):
            sum[i] += 1 if p[i] == yes else 0
    
    same_pixels = []
    for i in range(line_len):
        if sum[i] == 0: same_pixels.append([i, no])
        elif sum[i] == poss_no: same_pixels.append([i, yes])
    
    return same_pixels

def check_done(i, enum, cols_done, rows_done):
    if enum == row_enum: return rows_done[i]
    return cols_done[i]

def check_solved(rows_done, cols_done):
    return True if 0 not in rows_done and 0 not in cols_done else False

def get_col(matrix, j):
    return [matrix[i][j] for i in range(len(matrix))]

def update_done(enum, i, matrix, rows_done, cols_done):
    line = matrix[i] if enum == row_enum else get_col(matrix, i)
    if idk not in line:
        if enum == row_enum: rows_done[i] = 1
        else: cols_done[i] = 1

def update_poss(poss, i, val):
    return [p for p in poss if p[i] == val]

def find_ans(matrix, rows_poss, cols_poss, rows_done, cols_done):
    solved = False
    while not solved: 
        not_solved_rows = select_not_solved(rows_poss, rows_done, row_enum)
        not_solved_cols = select_not_solved(cols_poss, cols_done, col_enum)
        lines_todo = sorted(not_solved_cols + not_solved_rows) # sortuje je po najmniejszej ilości możliwości na które można ułożyć linie
        
        # sprawdzeni czy jestem w stanie iść do przodu
        _, i, enum = lines_todo[0]
        poss = rows_poss[i] if enum == row_enum else cols_poss[i]
        if poss == 0: return [] # nawrót
        
        if get_same_pixels(poss) == []: # nie jestem w stanie zrobić ruchu
            for l in rows_poss[i]:
                # kopiowanie
                _matrix = matrix.copy()
                _rows_poss = rows_poss.copy()
                _rows_poss[i].remove(l)
                _cols_poss = cols_poss.copy()
                _rows_done = rows_done.copy()
                _cols_done = cols_done.copy()
                
                # ustawianie rzędu
                for j in range(len(matrix[0])):
                    val = l[j]
                    r_idx, c_idx = (i, j) if row_enum == enum else(j, i)
                    if matrix[r_idx][c_idx] == idk:
                        matrix[r_idx][c_idx] = val
                        
                        if enum != row_enum: _rows_poss[r_idx] = update_poss(_rows_poss[r_idx], c_idx, val)
                        else: _cols_poss[c_idx] = update_poss(_cols_poss[c_idx], r_idx, val)
                    update_done(enum, i, _matrix, _rows_done, _cols_done)
                
                # ustawiłem już rząd ide głębiej
                f = find_ans(_matrix, _rows_poss, _cols_poss, _rows_done, _cols_done)
                if f != []: return f # znalazłem odpowiedz
            # sprawdziłem wszystkie opcje i wszystkie były złe wracam się 
            return []
                
        # ustawia pixele o których wiemy jak będą wyglądały
        for _, i, enum in lines_todo:
            if not check_done(i, enum, cols_done, rows_done):
                poss = rows_poss[i] if enum == row_enum else cols_poss[i] # możliwe wypełnienia lini
                same_pixels = get_same_pixels(poss)
                
                for j, val in same_pixels:
                    r_idx, c_idx = (i, j) if row_enum == enum else (j, i)
                    if matrix[r_idx][c_idx] == idk:
                        matrix[r_idx][c_idx] = val

                        # usówamie możliwości które się nie zgadzająz nowym pixelem
                        if enum != row_enum: rows_poss[r_idx] = update_poss(rows_poss[r_idx], c_idx, val)
                        else: cols_poss[c_idx] = update_poss(cols_poss[c_idx], r_idx, val)
                update_done(enum, i, matrix, rows_done, cols_done) # sprawdza czy linia jest ukończona
        solved = check_solved(rows_done, cols_done)
    return matrix

def policz(rows_no, cols_no, rows, cols):
    matrix = [[idk for _ in range(cols_no)] for _ in range(rows_no)]
    
    rows_done = [0] * rows_no
    cols_done = [0] * cols_no
    
    # liczenie wszystkich możliwych ustawień
    rows_poss = make_poss(rows, cols_no)
    cols_poss = make_poss(cols, rows_no)
    
    for u in rows_poss:
        shuffle(u)
    for u in cols_poss:
        shuffle(u)
    
    return find_ans(matrix, rows_poss, cols_poss, rows_done, cols_done)
    
def main():
    # wczytaj dane
    input = open('zad_input.txt')
    n, m = map(int, input.readline().split())
    rows = [list(map(int, input.readline().split())) for _ in range(n)]
    cols = [list(map(int, input.readline().split())) for _ in range(m)]
    input.close() 
     
    # policz
    matrix = policz(n, m, rows, cols)
    
    #wpyisz dane
    output = open('zad_output.txt', 'w')
    for i in range(n):
        for j in range(m):
            output.write('#' if matrix[i][j] == yes else '.')
        output.write('\n')
    
    output.close()

if __name__ == "__main__":
    main()