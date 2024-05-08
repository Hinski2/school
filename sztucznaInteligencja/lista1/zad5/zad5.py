import random

def change_pixel(nanogram, row, col):
    nanogram[row][col] ^= 1
    
def get_col(nanogram, col):
    return [row[col] for row in nanogram]

def find_dist(wiersz, blok, l, r):
    ans = l
    local_max, global_max = 0, 0
    
    for i in range(l, l + blok):
        if(wiersz[i] == 0):
            local_max += 1
            
    for i in range(l + blok, r):
        local_max += wiersz[i]
        
    global_max = local_max
    for i in range(l, r - blok):
        if wiersz[i] == 0:
            local_max -= 1
        else:
            local_max += 1
            
        if wiersz[i + blok] == 0:
            local_max += 1
        else:
            local_max -= 1
            
        if local_max < global_max:
            ans = i + 1
            global_max = local_max
            if local_max == 0:
                break
            
    return ans
        

def opt_dist(row, desc):
    l, r = 0, len(row)
    left = sum(desc) + len(desc)
    ans = 0
    blocks = [0 for _ in range(r)]
    
    for blok in desc:
        left -= blok + 1
        l = find_dist(row, blok, l, r - left)
        for i in range(l, l + blok):
            blocks[i] = 1
        l += blok + 1
        
    for i in range(r):
        if row[i] != blocks[i]:
            ans += 1
            
    return ans
    

def col_opt_dist(nanogram, col_desc, col):
    return opt_dist(get_col(nanogram, col), col_desc[col])

def make_nanogram(n, m, row_desc, col_desc):
    limit = 500
    while True:
        col_todo = [] # lista kolumn do poprawy
        row_todo = [] # lista wierszy do poprawy 
        nanogram = []
        
        # randomowe generowanie nanogramu
        for i in range(n):
            nanogram.append([random.randint(0, 1) for _ in range(m)])
        
        # tworzenie col_todo
        for i in range(m):
            if opt_dist(get_col(nanogram, i), col_desc[i]) > 0:
                col_todo.append(i)
        
        # tworzenie row_todo
        for i in range(n):
            if opt_dist(nanogram[i], row_desc[i]) > 0:
                row_todo.append(i)
        
        # naprawianie nanogramu
        for itr in range(limit):
            highest_diff = float("-inf")
            high_diff_changes = []               # lista pikseli krorych zmiana jest dość opłacalna
            best_changes = []                    # lista pikseli których zmiana jest lejlepsza
            to_change_row, to_change_col = 0, 0  # wiersz i kolumna do zmiany
            
            # wybieram cyz zmienie kolune czy wiersz   
            choice = random.randint(0 if col_todo else 1, 1 if row_todo else 0)
            
            # zmiana kolumny
            if choice == 0:
                # sprawdzam jak bardzo kolumna różni się od tego jak powinna wyglądać
                col = random.choice(col_todo)
                col_diff = col_opt_dist(nanogram, col_desc, col)
                
                # sprawdzam co mi da zmiana konkretnych pikseli w kolumnie
                for row in range(n):
                    row_diff = opt_dist(nanogram[row], row_desc[row])
                    diff = col_diff + row_diff
                    
                    # sprawdzam jak dużo da mi zmiana piksela
                    change_pixel(nanogram, row, col)
                    diff -= col_opt_dist(nanogram, col_desc, col) + opt_dist(nanogram[row], row_desc[row])
                    change_pixel(nanogram, row, col)
                    
                    if diff >= highest_diff:
                        highest_diff = diff
                        high_diff_changes.append((row, diff))
                        
                # tworzenie best_changes
                for change in high_diff_changes:
                    if change[1] == highest_diff:
                        best_changes.append(change[0])
                
                # zmiana wiersza i kolumny
                to_change_row = random.choice(best_changes)
                to_change_col = col
                change_pixel(nanogram, to_change_row, to_change_col)
            
            #zmiana wiersza          
            else:
                #sprawdzam jak bardzo wiersz różni się od tego jak powienin wyglądać
                row = random.choice(row_todo)
                row_diff = opt_dist(nanogram[row], row_desc[row])
                
                #sprawdzam co mi da zmiana konkretnych kolumn w wierszu
                for col in range(m):
                    col_diff = col_opt_dist(nanogram, col_desc, col)
                    diff = col_diff + row_diff
                    
                    #sprawdzam jak dużo da mi zmiana piksela
                    change_pixel(nanogram, row, col)
                    diff -= col_opt_dist(nanogram, col_desc, col) + opt_dist(nanogram[row], row_desc[row])
                    change_pixel(nanogram, row, col)
                    
                    if diff >= highest_diff:
                        highest_diff = diff
                        high_diff_changes.append((col, diff))
                        
                # tworzenie best_change
                for change in high_diff_changes:
                    if change[1] == highest_diff:
                        best_changes.append(change[0])
                
                # zmiana wiersza i kolumny
                to_change_row = row
                to_change_col = random.choice(best_changes)
                change_pixel(nanogram, to_change_row, to_change_col)
            
            # aktualizuje stan wierszy i kolumn
            res = opt_dist(nanogram[to_change_row], row_desc[to_change_row])
            if to_change_row in row_todo:
                if res == 0: 
                    row_todo.remove(to_change_row)
            elif res != 0:
                row_todo.append(to_change_row)
                
            res = col_opt_dist(nanogram, col_desc, to_change_col)
            if to_change_col in col_todo:
                if res == 0:
                    col_todo.remove(to_change_col)
            elif res != 0:
                col_todo.append(to_change_col)
                
            # sprawdzam czy ułożyłem już nanogram
            if len(row_todo) == 0 and len(col_todo) == 0:
                return nanogram
            
            # czyszczenie struktur
            highest_diff = float("-inf")
            high_diff_changes = []               
            best_changes = [] 

def main():
    n, m = 0, 0 #rozmiar nanogramu
    row_desc, col_desc = [], [] #lista na opis wiersza i kolumn
    
    # wczytywanie danych
    with open("zad5_input.txt") as file:
        n, m = map(int, file.readline().split())
        row_desc = [[int(x) for x in file.readline().split()] for _ in range(n)]
        col_desc = [[int(x) for x in file.readline().split()] for _ in range(m)]
    
    # tworzenie obrazka
    nanogram = make_nanogram(n, m, row_desc, col_desc)
    
    # wypisanie odpowiedzi
    with open("zad5_output.txt", 'w') as output:
        for row in nanogram:
            row_str = ""
            for val in row:
                if val == 1: row_str += '#'
                else: row_str += '.'
            row_str += '\n'
            output.write(row_str)
                    
if __name__ == "__main__":
    main()