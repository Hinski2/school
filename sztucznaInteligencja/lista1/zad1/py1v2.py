from collections import deque
import sys
inf = 1000

#dp do odpowiedz, oraz backtrack, by wiedzieć gdzie zrobić ruch
dp = [[[[[[[inf for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(2)]
backtrack = [[[[[[[[] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(2)]

#ruchy króla
vector_king = [(-1, -1), (-1, 0), (-1, 1),
               (0, -1), (0, 1),
               (1, -1), (1, 0), (1, 1)]

#czy nie wyszedłem poza plansze
def valid_position(x, y):
    return 0 <= x < 8 and 0 <= y < 8

#czy króle stoją ok
def valid_kings(wk, bk):
    return False if abs(wk[0] - bk[0]) <= 1 and abs(wk[1] - bk[1]) <= 1 else True

#czy wierza atakuje czarnego króla
def rook_attacks(wr, bk):
    return wr[0] == bk[0] or wr[1] == bk[1]

def black_king_attacks_rook(wk, wr, bk):
    can_attack = abs(wr[0] - bk[0]) <= 1 and abs(wr[1] - bk[1]) <= 1
    can_defend = abs(wr[0] - wk[0]) <= 1 and abs(wr[1] - wk[1]) <= 1

    return can_attack and not can_defend

#czy ustawienie prowadzi do mata
def is_mat(wk, wr, bk):
    #sprawdzam czy jest szach
    if not rook_attacks(wr, bk): return 0

    #jest szach sprawdzam czy jest mat
    for ruch in vector_king:
        new_bk = (bk[0] + ruch[0], bk[1] + ruch[1])
        if not valid_position(new_bk[0], new_bk[1]): continue
        if not valid_kings(wk, new_bk): continue
        if rook_attacks(wr, new_bk): continue
        
        #udało sie uciec new_bk więc nie ma mata
        return False
    
    #nie udało mu sie uciec, sprawdzam w takim razie czy moze zbić wierze
    if black_king_attacks_rook(wk, wr, bk): return False
    return True #jest mat


#tworzenie odpowiedzi
def bfs():
    queue = deque()
    add_initial_mat_positions(queue)
    
    while queue:
        ustawienie = queue.popleft()
        option, wk, wr, bk, distance, come_from = ustawienie
        
        if option == 0 and wk == (0, 1) and wr == (4, 0) and bk == (0, 5):
            pass
        
        if dp[option][wk[0]][wk[1]][wr[0]][wr[1]][bk[0]][bk[1]] > distance:
            dp[option][wk[0]][wk[1]][wr[0]][wr[1]][bk[0]][bk[1]] = distance
            backtrack[option][wk[0]][wk[1]][wr[0]][wr[1]][bk[0]][bk[1]] = come_from
        else: continue
        
        if option == 0: #opcja ruch czarnych
            if rook_attacks(wr, bk): continue 
            for ruch in vector_king:
                new_bk = (bk[0] + ruch[0], bk[1] + ruch[1])
                if new_bk == wk or new_bk == wr: continue #nachodzą na siebie
                if not valid_position(new_bk[0], new_bk[1]): continue #poza plansza
                if not valid_kings(wk, new_bk): continue #króle za blisko siebie
                
                #położenie jest ok, sprawdzma cyz sie opłaca je sprawdzać
                if dp[option ^ 1][wk[0]][wk[1]][wr[0]][wr[1]][new_bk[0]][new_bk[1]] > distance + 1:
                    queue.append((option ^ 1, wk, wr, new_bk, distance + 1, [option, wk, wr, bk]))
                
        else: #opcja ruch białych
            #ruch królem
            for ruch in vector_king:
                new_wk = (wk[0] + ruch[0], wk[1] + ruch[1])
                if new_wk == bk or new_wk == wr: continue #nachodzą na siebie
                if not valid_position(new_wk[0], new_wk[1]): continue #poza plansza
                if not valid_kings(new_wk, bk): continue #króle za blisko siebie
                
                #położenie jest ok, sprawdzma cyz sie opłaca je sprawdzać
                if dp[option ^ 1][new_wk[0]][new_wk[1]][wr[0]][wr[1]][bk[0]][bk[1]] > distance + 1:
                    queue.append((option ^ 1, new_wk, wr, bk, distance + 1, [option, wk, wr, bk]))

            #ruch wierzą
            for i in range(-7, 8):
                new_wr = (wr[0] + i, wr[1])
                if new_wr == wk or new_wr == bk: continue
                if not valid_position(new_wr[0], new_wr[1]): continue
                
                #położenie ok
                if dp[option ^ 1][wk[0]][wk[1]][new_wr[0]][new_wr[1]][bk[0]][bk[1]] > distance + 1:
                    queue.append((option ^ 1, wk, new_wr, bk, distance + 1, [option, wk, wr, bk]))
            for j in range(-7, 8):
                new_wr = (wr[0], wr[1] + j)
                if new_wr == wk or new_wr == bk: continue
                if not valid_position(new_wr[0], new_wr[1]): continue
                
                #położenie ok
                if dp[option ^ 1][wk[0]][wk[1]][new_wr[0]][new_wr[1]][bk[0]][bk[1]] > distance + 1:
                    queue.append((option ^ 1, wk, new_wr, bk, distance + 1, [option, wk, wr, bk]))
            
#sprawdzanie jakie pozycje dają mata
def add_initial_mat_positions(queue):
    for wk_x in range(8): #wynierabie białego króal
        for wk_y in range(8):
            wk = (wk_x, wk_y)
            for wr_x in range(8): #wybieranie białej wierzy
                for wr_y in range(8):
                    wr = (wr_x, wr_y)
                    if wr == wk: continue
                    for bk_x in range(8): #wynieranie czarnego kóla
                        for bk_y in range(8):
                            bk = (bk_x, bk_y)
                            if bk == wk or bk == wr: continue
                            if not valid_kings(wk, bk): continue
                            
                            #ustawienie jest ok
                            if is_mat(wk, wr, bk):
                                queue.append((1, wk, wr, bk, 0, [1, wk, wr, bk]))
                                queue.append((0, wk, wr, bk, 0, [0, wk, wr, bk]))
                                    
#main
# with open('rezultaty_koncowek_szachowych.txt', 'w') as file:
#     for option in range(2):
#         for wkx in range(8):
#             for wky in range(8):
#                 for wrx in range(8):
#                     for wry in range(8):
#                         for bkx in range(8):
#                             for bky in range(8):
#                                 file.write(f"{dp[option][wkx][wky][wrx][wry][bkx][bky]} " + ' '.join(map(str, backtrack[option][wkx][wky][wrx][wry][bkx][bky])) + '\n')

#zamiana danych wejściowych na bardziej przyjazne 
def chess_coord_to_tuple(coord):
    col = ord(coord[0].upper()) - ord('A')
    row = int(coord[1]) - 1
    return (row, col)

def transform(line):
    line = line.strip()
    parts = line.split()
    
    option = 0 if parts[0] == 'black' else 1
    wk = chess_coord_to_tuple(parts[1])
    wr = chess_coord_to_tuple(parts[2])
    bk = chess_coord_to_tuple(parts[3])
    
    return option, wk, wr, bk

#funkcja wypisująca optymalną sekwencje ruchów
def make_debug(option, wk, wr, bk):
    next_move = backtrack[option][wk[0]][wk[1]][wr[0]][wr[1]][bk[0]][bk[1]]
    if next_move[1] == wk and next_move[2] == wr and next_move[3] == bk:
        print("mat")
        return
    
    print(next_move[1], next_move[2], next_move[3])
    make_debug(next_move[0], next_move[1], next_move[2], next_move[3])
    
    
def main():
    bfs()
    with open('rezultaty_koncowek_szachowych.txt', 'w') as file:
        for option in range(2):
            for wkx in range(8):
                for wky in range(8):
                    for wrx in range(8):
                        for wry in range(8):
                            for bkx in range(8):
                                for bky in range(8):
                                    file.write(f"{dp[option][wkx][wky][wrx][wry][bkx][bky]} " + ' '.join(map(str, backtrack[option][wkx][wky][wrx][wry][bkx][bky])) + '\n')
    

                    
if __name__ == "__main__":
    main()
                                
                            
    


        
        
    