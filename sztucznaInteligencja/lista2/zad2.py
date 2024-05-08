from collections import deque
import random

# konwertuje vektor na chara
translate = {
    (0, 1): 'R',
    (0, -1): 'L',
    (1, 0): 'D',
    (-1, 0): 'U'
}

# lista możliwych ruchów
vector = [
    (0, 1),
    (0, -1),
    (1, 0),
    (-1, 0)
]

def lower_uncertanity(plansza, n, m):
    pos = []
    for i in range(n):
        for j in range(m):
            if plansza[i][j] == 'S' or plansza[i][j] == 'B':
                pos.append((i, j))
                
    pos = tuple(pos)
    queue = deque([(pos, '')])  # kolejka do bfs
    lowest = float('inf')       # najmniejsza uzyskana liczba agentów na mapie
    vis = {pos}                 # odwiedzone wierzchołki
    
    while queue:
        pos, path = queue.popleft()
        
        if len(pos) > lowest: continue #jeśli znalazłem lepsze ustawienie
        if len(pos) == 1: break #znalazłem ustawienie w którym jest jedne agent
        
        for dx, dy in vector:
            _pos = []
            for (x, y) in pos:
                _x, _y = x + dx, y + dy
                
                if plansza[_x][_y] == '#':
                    if (x, y) not in _pos: _pos.append((x, y))
                else:
                    if (_x, _y) not in _pos: _pos.append((_x, _y))
                    
            _pos = tuple(_pos)
            if _pos in vis: continue
            vis.add(_pos)
            queue.append((_pos, path + translate[(dx, dy)]))
            
            lowest = min(lowest, len(_pos))
            
    return (pos[0], path)          
        

def find_path(plansza, n, m):
    # zmniejsza liczbę agentów do 1
    start_pos, start_path = lower_uncertanity(plansza, n, m)
    start_pos = tuple(start_pos)
    
    #bfs
    queue = deque([(start_pos, start_path)])
    vis = {start_pos}
    while(queue):
        (x, y), path = queue.popleft()
        
        # jeżeli dotarłem do końca 
        if plansza[x][y] == 'G' or plansza[x][y] == 'B':
            break
        
        for dx, dy in vector:
            _x, _y = x + dx, y + dy
            if plansza[_x][_y] == '#': continue
            if (_x, _y) in vis: continue
            
            queue.append(((_x, _y), path + translate[(dx, dy)]))
            vis.add((_x, _y))
    
    return path
    
def main():
    # wczytanie danych
    plansza = []
    with open("zad_input.txt") as file:
        for row in file:
            plansza.append(row[:-1])
    
    #znalezienie ścieżki 
    path = find_path(plansza, len(plansza), len(plansza[0]))
    
    #wypisanie danych
    with open("zad_output.txt", 'w') as output:
        output.write(path)

if __name__ == "__main__":
    main()