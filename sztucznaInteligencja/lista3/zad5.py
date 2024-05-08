def B(i,j):
    return 'B_%d_%d' % (i,j)

def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'

def get_col(j, C):
    return [B(c, j) for c in range(C)]

def get_row(i, R):
    return [B(i, r) for r in range(R)]

def imp3(lista):
    return f"{lista[1]} #==> ({lista[0]} #\/ {lista[2]}),"

# zwraca liste list 3 kolenjych zmiennych z listy 
def get3_consecutive(lista):
    return [[lista[i + j] for j in range(3)] for i in range(0, len(lista) - 2)]

def get_2x2(n, m):
    l = []
    for i in range(n - 1):
        for j in range(m - 1):
            l.append([B(i, j), B(i, j + 1), B(i + 1, j), B(i + 1, j + 1)])
    return l

def matrix_check(l):
    return f"({l[0]} #/\ {l[3]}) #<==> ({l[1]} #/\ {l[2]}),"

def check2x2(n, m):
    return map(matrix_check, get_2x2(n, m))

def consecutive_3_rows(n, m):
    cs = []
    for i in range(n):
        cs += map(imp3, get3_consecutive(get_row(i, n)))
    return cs
        
def consiecutive_3_cols(n, m):
    cs = []
    for i in range(m):
        cs += map(imp3, get3_consecutive(get_col(i, m)))
    return cs

def rows_sum(n, m, rows):
    cs = []
    for i in range(n):
        cs += ['(' + ' + '.join(get_row(i, n)) + ')' + ' #= ' + str(rows[i]) + ',']
    return cs

def cols_sum(n, m, cols):
    cs = []
    for i in range(m):
        cs += ['(' + ' + '.join(get_col(i, m)) + ')' + ' #= ' + str(cols[i]) + ',']
    return cs

def domains(bs):
    return [ q + ' in 0..1,' for q in bs ]

def known(triples):
    return [f"{B(u[0], u[1])} #= {u[2]}," for u in triples]
    
def storms(rows, cols, triples):
    writeln(':- use_module(library(clpfd)).')
    
    n = len(rows)
    m = len(cols)
    
    bs = [ B(i,j) for i in range(n) for j in range(m)] #tworzenie nazw zmiennych 
    
    writeln('solve([' + ', '.join(bs) + ']) :- ')
    
    # napisanie że zmienne są z przedziału [0, 1]
    cs = domains(bs)
     
    # warunek do tego że burze muszą być min 2x2
        # dla kazdych 3 następnych bloków a, b, c: jeśli b -> a || c
    cs += consecutive_3_rows(n, m) + consiecutive_3_cols(n, m)
        
    # warunek nie mogą stykać się rogami + ma by min 2x2
        # dla macierzy 2 x 2 [[a, b], [c, d]] jeśli a && c -> b && d
    cs += check2x2(n, m)
        
    # warunek suma w wierszu musi być równa radarowi
    cs += rows_sum(n, m, rows)
    
    # warunek suma w kolumnie musi być równa radorowi
    cs += cols_sum(n, m, cols)
    
    # dodanie informacji o punktach, o których wiemy jak mają być poklorowane
    cs += known(triples)

    output.write('\n'.join(cs) + '\n')
    # tu jest już git nie trzeba zmieniać 
    writeln('labeling([ff], [' +  ', '.join(bs) + ']).' )
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")

def writeln(s):
    output.write(s + '\n')

txt = open('zad_input.txt').readlines()
output = open('zad_output.txt', 'w')

rows = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []  #pola które wiemy jak są pokolorowane

for i in range(2, len(txt)):
    if txt[i].strip():
        triples.append(list(map(int, txt[i].split()))) #dodajemy info że pole w wierszu kolumnie jest 0/1

storms(rows, cols, triples)            
        