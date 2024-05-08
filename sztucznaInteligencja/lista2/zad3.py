from queue import PriorityQueue
from collections import deque

vector = [
    (1, 0),
    (-1, 0),
    (0, 1),
    (0, -1)
]

moves = ['U', 'D', 'R', 'L']
translate = {
    'U': (-1, 0),
    'D': (1, 0),
    'L': (0, -1),
    'R': (0, 1)
}

def find_dist(plansza, n, m):
    dist = [[float('inf')] * m for _ in range(n)] 
    queue = deque()
    
    for i in range(n):
        for j in range(m):
            if plansza[i][j] == 'B' or plansza[i][j] == 'G':
                queue.append(((i, j), 0))
    
    while queue:
        (x, y), d = queue.popleft()
        if dist[x][y] != float('inf'): continue
        dist[x][y] = d
        
        for dx, dy in vector:
            _x, _y = x + dx, y + dy
            if plansza[_x][_y] == '#': continue
            if dist[_x][_y] != float('inf'): continue
            
            queue.append(((_x, _y), d + 1))
    
    return dist


# zwraca max z odległości dla każdego agenta do najbliższego celu
def dist_heur(agent_pos, dist):
    ans = 0
    for (x, y) in agent_pos:
        ans = max(ans, dist[x][y])
    return ans

def rozproszenie_heur(agent_pos):
    return max(rozproszenie(agent_pos), 3 / 2)

def make_move(plansza, agent_pos, move):
    _agent_pos = []
    dx, dy = translate[move]
    
    for (x, y) in agent_pos:
        _x, _y = x + dx, y + dy
        if plansza[_x][_y] == '#':
            if (x, y) not in _agent_pos: _agent_pos.append((x, y))
        else:
            if (_x, _y) not in _agent_pos: _agent_pos.append((_x, _y))
        
    return _agent_pos

def rozproszenie(agent_pos):
    n = len(agent_pos)
    avg_x = sum([x for (x, _) in agent_pos]) / n
    avg_y = sum([y for (_, y) in agent_pos]) / n
    return sum([abs(avg_x - x) + abs(avg_y - y) for (x, y) in agent_pos]) / (2 * n)
    
def find_path(plansza, n, m):
    dist = find_dist(plansza, n, m) # dystans do najbliższego wyjscia z (x, y)
    starting_pos = []               # lista pozycji startujących
    empty_pos = 0                   # licznik pustych miejsc
    target_pos = []                 # lista pozycji końcowych
   
    # szukanie pozycji startowych / końcowych, liczenie pustych miejsc 
    for i in range(n):
        for j in range(m):
            if plansza[i][j] == 'S' or plansza[i][j] == 'B': starting_pos.append((i, j))
            elif plansza[i][j] == 'G' or plansza[i][j] == 'B': target_pos.append((i, j))
            elif plansza[i][j] == ' ': empty_pos += 1
    
    
    pq = PriorityQueue()
    pq.put((0, starting_pos, 0, "")) #koszt, pozycje_agentów, głębokość, path
    vis = {frozenset(starting_pos)}
    
    while pq:
        cost , agent_pos, d, path = pq.get()
        
        #jeżeli wszyscy agenci są na wyjsciu
        if all(plansza[x][y] == 'G' or plansza[x][y] == 'B' for (x, y) in agent_pos): 
            return path
        
        #robienie ruchu 
        for move in moves:
            _agent_pos = make_move(plansza, agent_pos, move)
            set = frozenset(_agent_pos)
            if set in vis: continue
            
            vis.add(set)
            dh = dist_heur(_agent_pos, dist) # max odl do końca od agenta 
            _cost = d + 1 + dh + (rozproszenie_heur(_agent_pos) if len(_agent_pos) > empty_pos else 0)
            
            pq.put((_cost, _agent_pos, d + 1, path + move))
            
            
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