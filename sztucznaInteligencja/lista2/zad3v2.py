from queue import PriorityQueue
from collections import deque
# python validator.py --cases 1 zad3 python zad3.py

def make_moves(labirynth, poses, move):
    new_poses = []
    dx = 0
    dy = 0

    if move == 'U':
            dx = -1
    elif move == 'D':
        dx = 1
    elif move == 'L':
        dy = -1
    else:
        dy = 1

    for i in range(len(poses)):
        old_pos = poses[i]
        new_pos = (old_pos[0] + dx, old_pos[1] + dy)
        if labirynth[new_pos[0]][new_pos[1]] == '#':
            new_pos = old_pos
        if new_pos not in new_poses:
            new_poses.append(new_pos)

    return new_poses

def bfs_heur(labirynth, pos):
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    queue = deque([(pos, 0)])
    visited = {pos}

    while(queue):
        (x, y), dist = queue.popleft()
        curr = labirynth[x][y]
        if curr == 'G' or curr == 'B':
            # print(dist)
            return dist
        for dx, dy in directions:
            new_x, new_y = x + dx, y + dy
            if labirynth[new_x][new_y] != '#' and (new_x, new_y) not in visited:
                queue.append(((new_x, new_y), dist + 1))
                visited.add((new_x, new_y))

    return float("inf")

def center_heur(pos):
    count = len(pos)
    avg_x = sum([x for (x, _) in pos]) / count
    avg_y = sum([y for (_, y) in pos]) / count
    return sum([abs(avg_x - x) + abs(avg_y - y) for (x, y) in pos]) / (2 * count)

def mann_heur(pos, targets):
    max = 0
    for p in pos:
        for t in targets:
            dist = abs(p[0] - t[0]) + abs(p[1] - t[1])
            if dist > max:
                max = dist
    return max

def lookup_heur(labirynth, pos, lookup):
    max = 0

    for (x, y) in pos:
        if lookup[x][y] != -1:
            dist = lookup[x][y]
        else:
            dist = bfs_heur(labirynth, (x, y))
            lookup[x][y] = dist
        if dist > max:
            max = dist
    # print(max)
    return max

def generate_path(labirynth, sizes):
    lookup = []
    starting = []
    empty = 0
    targets = []

    for i in range(sizes[0]):
        lookup.append([])
        for j in range(sizes[1]):
            lookup[i].append(-1)
            curr = labirynth[i][j]
            if curr == 'S' or curr == 'B':
                starting.append((i, j))
            elif curr == 'G' or curr == 'B':
                targets.append((i, j))
            elif curr == ' ':
                empty += 1

    moves = ['U', 'D', 'R', 'L']
    queue = PriorityQueue()
    queue.put((0, (starting, 0, "")))
    visited = set(frozenset(starting))
    min_heur = len(starting) / 50

    while queue:
        curr = queue.get()
        new_steps = curr[1][1] + 1
        if all(labirynth[x][y] == 'G' or labirynth[x][y] == 'B' for (x, y) in curr[1][0]):
            return curr[1][2]
        for move in moves:
            pos = make_moves(labirynth, curr[1][0], move)
            frozen_pos = frozenset(pos)
            if frozen_pos not in visited:
                visited.add(frozen_pos)
                # 0.15*(len(curr[1][0]) - len(pos))
                # (max(min_heur, center_heur(pos)) if empty == 0 and  else 0)
                l_heur = lookup_heur(labirynth, pos, lookup)
                if curr[1][2] + move == "RRUURURRRURRRUURRRRRDRRDDDDD":
                    pass
                queue.put((new_steps + l_heur + (max(min_heur, center_heur(pos)) if empty == 0 and mann_heur(pos, targets) < l_heur else 0), (pos, new_steps, curr[1][2] + move)))

    return "Not found"   

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        labirynth = f.readlines()
        path = generate_path(labirynth, (len(labirynth), len(labirynth[0]) - 1))
        # print(path)
        with open("zad_output.txt", 'w') as o:
            o.write(path)