import sys
inf = 1000

dp = [[[[[[[inf for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(2)]
backtrack = [[[[[[[[] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(2)]
""" tworzenie tablicy dp i backtrack [2] [8][8] [8][8] [8][8]
    1) opcja 0: czarne zaczynają
       opcja 1: białe zaczynają
    2) koortynaty biały król
    3) koordynaty biała wierza
    4) koordynaty czarny król 
    łącznie 524'288 opcji
"""

#generator lini z pliku
def read_lines_from_file(filename):
    with open(filename, 'r') as file:
        for line in file:
            yield line.strip()
            
def parse(line):
    parts = line.split()
    if len(parts) == 1:
        return int(parts[0]), None, None, None, None
    else:
        ans = int(parts[0])
        option = int(parts[1])


        # Scala stringi, aby uzyskać pełne reprezentacje krotek
        wk_str = parts[2] + parts[3]  # '(1,' + '0)' => '(1,0)'
        wr_str = parts[4] + parts[5]  
        bk_str = parts[6] + parts[7]
        
        wk = tuple(map(int, wk_str.strip("()").split(',')))
        wr = tuple(map(int, wr_str.strip("()").split(',')))
        bk = tuple(map(int, bk_str.strip("()").split(',')))

        return ans, option, wk, wr, bk

#wczytywanie odpowiedzi
def load_results(filename):
    lines_generator = read_lines_from_file(filename)
    
    for option in range(2):
        for wkx in range(8):
            for wky in range(8):
                for wrx in range(8):
                    for wry in range(8):
                        for bkx in range(8):
                            for bky in range(8):
                                line = next(lines_generator)
                                        
                                ans, opt, wk, wr, bk = parse(line)
                                    
                                dp[option][wkx][wky][wrx][wry][bkx][bky] = ans
                                backtrack[option][wkx][wky][wrx][wry][bkx][bky] = [opt, wk, wr, bk]


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
    
#czytywanie pliku
def main():
    filename = "rezultaty_koncowek_szachowych.txt"
    
    #sprawdzanie argumentów
    debug_mode = False
    if len(sys.argv) > 1 and sys.argv[1] == 'debug':
        debug_mode = True
    
    #wczytywanie odpowiedzi 
    load_results(filename)
    
    #wczytywanie pliku z zadania
    plik = open('zad1_output.txt', 'w')
    with open('zad1_input.txt', 'r') as file:
        for line in file:
            option, wk, wr, bk = transform(line)
            option ^= 1
            DP = dp[option][wk[0]][wk[1]][wr[0]][wr[1]][bk[0]][bk[1]] #ilość ruchów do szacha 
            if DP == inf:
                # print("INF")
                plik.write("INF")
                continue
            else:
                # print(DP)
                plik.write(str(DP))
                if debug_mode: #opcja z debuge
                    print(wk, wr, bk)
                    make_debug(option, wk, wr, bk)
    plik.close()
                
if __name__ == "__main__":
    main()