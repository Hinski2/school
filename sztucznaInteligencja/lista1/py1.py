from collections import deque
inf = 1000

dp = [[[[[[[inf for _ in range(2)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)]
backtrack = [[[[[[[[] for _ in range(2)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)] for _ in range(8)]
""" tworzenie tablicy dp i backtrack [2] [8][8] [8][8] [8][8]
    1) opcja 0: czarne zaczynają
       opcja 1: białe zaczynają
    2) koortynaty biały król
    3) koordynaty biała wierza
    4) koordynaty czarny król 
    łącznie 524'288 opcji
"""
queue = deque()
vector_king = [[-1, -1], [-1, 0], [-1, 1],
               [0, -1], [0, 1],
               [1, -1], [1, 0], [1, 1]]

def valid_coord(x, y):
    return x >= 0 and y < 8

def valid_kings(ckx, cky, bkx, bky):
    return abs(ckx - bkx) >= 2 or abs(cky - bky) >= 2

def bije_wierza(ckx, cky, bwx, bwy):
    if ckx == bwx or cky == bwy: return False
    return True

def mat(bkx, bky, bwx, bwy, ckx, cky):
    #sprawdzam czy jest szach
    if 
    

    #jest szach sprawdzam czy jest mat
    for ruch in vector_king:
        x = ckx + ruch[0]
        y = cky + ruch[1]

        if not valid_coord(x, y): continue
        if not valid_kings(x, y, bkx, bky): continue
        if not valid_rook(x, y, bwx, bwy): continue


for opcja in range(2):
    for bk_x in range(8):
        for bk_y in range(8):
            for bw_x in range(8):
                for bw_y in range(8):
                    if (bk_x, bk_y) == (bw_x, bw_y): continue #pionki nachodzą na siebie
                    for ck_x in range(8):
                        for ck_y in range(8):
                            if (bw_x, bw_y) == (ck_x, ck_y): continue #pionki nachodzą na siebnei
                                if mat





with open('zad1_input.txt', 'r') as plik:
    zawartosc = plik.read()