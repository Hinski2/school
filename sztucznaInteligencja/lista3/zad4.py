import sys
import subprocess

def V(i,j):
    return 'V%d_%d' % (i,j)
    
def domains(Vs):
    return [ q + ' in 1..9' for q in Vs ]
    
def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'
    
def get_column(j):
    return [V(i,j) for i in range(9)] 
            
def get_raw(i):
    return [V(i,j) for j in range(9)]

def get_part(x):
    l = []
    for i in range(3):
        for j in range(3):
            l.append(V(x[0] + i, x[1] + j))
    return l
                           
def start(i):
    return ((i % 3) * 3, (i // 3) * 3)
                           
def partial():
    return [ all_different(get_part(start(i))) for i in range(9)] 
    
def horizontal():   
    return [ all_different(get_raw(i)) for i in range(9)]

def vertical():
    return [all_different(get_column(j)) for j in range(9)]

def print_constraints(Cs, indent, d):
    position = indent
    print (indent * ' ', end='', file=file)
    for c in Cs:
        print (c + ',', end=' ', file=file)
        position += len(c)
        if position > d:
            position = indent
            print (file=file)
            print (indent * ' ', end='', file=file)

      
def sudoku(assigments):
    variables = [ V(i,j) for i in range(9) for j in range(9)]
    
    print (':- use_module(library(clpfd)).', file=file)
    print ('solve([' + ', '.join(variables) + ']) :- ', file = file)
    
    
    cs = domains(variables) + vertical() + horizontal() + partial()
    for i,j,val in assigments:
        cs.append( '%s #= %d' % (V(i,j), val) )
    
    print_constraints(cs, 4, 70),
    print (file=file)
    print ('    labeling([ff], [' +  ', '.join(variables) + ']).', file=file )
    print (file=file)
  
    # Wypisuje kod Prologa na standardowe wyjście
    wypisanie_rozw = """
:- initialization(run_solve).

run_solve :-
    solve(X),
    write(X), nl,
    halt.
    """
    print(wypisanie_rozw, file=file)

if __name__ == "__main__":
    raw = 0
    triples = []
    
    file = open('zad_input.txt')
    for x in file:
        x = x.strip()
        if len(x) == 9:
            for i in range(9):
                if x[i] != '.':
                    triples.append( (raw,i,int(x[i])) ) 
            raw += 1
    file.close()
    
    file = open('solution.pl', 'w')
    sudoku(triples)
    file.close()
    
    # urochomienie prologa
    result = subprocess.run(['swipl', '-q', '-s', 'solution.pl'], capture_output=True, text=True)
    file = open('zad_output.txt', 'w')
    file.write(result.stdout)
    file.close()
    
    
"""
89.356.1.
3...1.49.
....2985.
9.7.6432.
.........
.6389.1.4
.3298....
.78.4....
.5.637.48

53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79

3.......1
4..386...
.....1.4.
6.924..3.
..3......
......719
........6
2.7...3..
.........
"""    
