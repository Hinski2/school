from queue import PriorityQueue
from itertools import combinations
from random import shuffle
from copy import deepcopy

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

def get_same_pixels(poss, line):
    poss_no = len(poss)
    if poss_no == 0: return []
    
    line_len = len(poss[0])
    sum = [0] * line_len
    for p in poss:
        for i in range(line_len):
            sum[i] += 1 if p[i] == yes else 0
    
    same_pixels = []
    for i in range(line_len):
        if sum[i] == 0 and line[i] != no: same_pixels.append([i, no])
        elif sum[i] == poss_no and line[i] != yes: same_pixels.append([i, yes])
    
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

def removed_poss(poss, i, val):
    return [p for p in poss if p[i] != val]

def valid(matrix, rows, cols):
    def get_segments(line):
        segments = []
        count = 0
        for value in line:
            if value == 1:
                count += 1
            elif count > 0:
                segments.append(count)
                count = 0
        if count > 0:
            segments.append(count)
        return segments

    # Sprawdzamy wiersze
    for i, row in enumerate(matrix):
        if get_segments(row) != rows[i]:
            return False

    # Sprawdzamy kolumny
    num_cols = len(matrix[0])
    for j in range(num_cols):
        col = [matrix[i][j] for i in range(len(matrix))]
        if get_segments(col) != cols[j]:
            return False

    return True

def wypisz(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end=' ')
            if matrix[i][j] != -1: print(' ', end='') 
        print()
    print()
    
def give_back_removed_poss(enum, n, m, removed_poss_rows, removed_poss_cols, rows_poss, cols_poss):
    if enum != row_enum:
        for g in range(n):
            rows_poss[g] += removed_poss_rows[g]
    else:
        for g in range(m):
            cols_poss[g] += removed_poss_cols[g]
    
def get_coll(matrix, j):
    return [matrix[i][j] for i in range(len(matrix))]

def find_ans(matrix, rows_poss, cols_poss, rows_done, cols_done, rows, cols):
    # wypisz(matrix)
    # szukam tego co moge ustawić 
    not_solved_rows = []
    not_solved_cols = []
    lines_todo = []
    
    #sprawdzenie
    for j in range(len(rows_poss)):
        if len(rows_poss[j]) == 0 and not rows_done[j]:
            return []
        
    for j in range(len(cols_done)):
        if len(cols_poss[j]) == 0 and not cols_done[j]:
            return []
    
    # ustawiam to co moge 
    solved, change = False, True
    while not solved and change: 
        change = False
        not_solved_rows = select_not_solved(rows_poss, rows_done, row_enum)
        not_solved_cols = select_not_solved(cols_poss, cols_done, col_enum)
        lines_todo = sorted(not_solved_cols + not_solved_rows) # sortuje je po najmniejszej ilości możliwości na które można ułożyć linie
        
        # ustawia pixele o których wiemy jak będą wyglądały
        for ammount, i, enum in lines_todo:
            if ammount == 0: return []
            if not check_done(i, enum, cols_done, rows_done):
                poss = rows_poss[i] if enum == row_enum else cols_poss[i] # możliwe wypełnienia lini
                line = matrix[i] if enum == row_enum else get_coll(matrix, i)
                same_pixels = get_same_pixels(poss, line)
                
                for j, val in same_pixels:
                    r_idx, c_idx = (i, j) if row_enum == enum else (j, i)
                    if matrix[r_idx][c_idx] == idk:
                        if matrix[r_idx][c_idx] != val:
                            matrix[r_idx][c_idx] = val
                            change = True

                            # usówamie możliwości które się nie zgadzająz nowym pixelem
                            if enum != row_enum: 
                                rows_poss[r_idx] = update_poss(rows_poss[r_idx], c_idx, val)
                            else: 
                                cols_poss[c_idx] = update_poss(cols_poss[c_idx], r_idx, val)
                                
                update_done(enum, i, matrix, rows_done, cols_done) # sprawdza czy linia jest ukończona
        solved = check_solved(rows_done, cols_done)

    #sprawdzenie
    for j in range(len(rows_poss)):
        if len(rows_poss[j]) == 0 and not rows_done[j]:
            return []
        
    for j in range(len(cols_done)):
        if len(cols_poss[j]) == 0 and not cols_done[j]:
            return []
        
    # jeśli mam gotowy nonogram to go zwracam
    if solved:
        if valid(matrix, rows, cols): return matrix
        else: return []
    
    # jeśli nie jsest gotowy to robie kopie oraz ustawiam ten wiersz / kolumne
        # którą ma najmniej możliwości ustawienia 
        # jak ją już ustawie to robie wywołąnie find_ans jeśli zwróci [] to ustawiam kolejną możliwość
        # dla wiersza/kolumny aż do końca możliwości
        # jeśli przejżałem już wszystkie możliwości i nic nie znalazłem to zwracam []
    
    not_solved_rows = select_not_solved(rows_poss, rows_done, row_enum)
    not_solved_cols = select_not_solved(cols_poss, cols_done, col_enum)
    lines_todo = sorted(not_solved_cols + not_solved_rows) # sortuje je po najmniejszej ilości możliwości na które można ułożyć linie
    
    _, i, enum = lines_todo[0]
    to_check = deepcopy(rows_poss[i] if enum == row_enum else cols_poss[i])
    for u in to_check:
        _matrix = deepcopy(matrix)
        _rows_poss = deepcopy(rows_poss)
        _cols_poss = deepcopy(cols_poss)
        _rows_done = deepcopy(rows_done)
        _cols_done = deepcopy(cols_done)
        
        for j in range(len(u)):
            val = u[j]
            r_idx, c_idx = (i, j) if row_enum == enum else (j, i)
            if _matrix[r_idx][c_idx] == idk:
                _matrix[r_idx][c_idx] = val

                # usówamie możliwości które się nie zgadzająz nowym pixelem
                if enum != row_enum: 
                    _rows_poss[r_idx] = update_poss(_rows_poss[r_idx], c_idx, val)
                else: 
                    _cols_poss[c_idx] = update_poss(_cols_poss[c_idx], r_idx, val)
                
        update_done(enum, i, _matrix, _rows_done, _cols_done) # sprawdza czy linia jest ukończona
        
        if check_solved(_rows_done, _cols_done):
            if valid(_matrix, rows, cols): return _matrix
            else: continue
        
        # wszystko już jest ustawione
        ans = find_ans(_matrix, _rows_poss, _cols_poss, _rows_done, _cols_done, rows, cols)
        if ans != []:
            return ans
    return []
        

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
    
    return find_ans(matrix, rows_poss, cols_poss, rows_done, cols_done, rows, cols)
    
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