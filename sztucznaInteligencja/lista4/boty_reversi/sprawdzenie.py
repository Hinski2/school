import random
import copy

# Definicje stałych
black, white, empty = range(3)
max_player, min_player = black, white
vector_moves = [(i, j) for i in [-1, 0, 1] for j in [-1, 0, 1] if (i, j) != (0, 0)]

# Klasa reprezentująca węzeł drzewa ruchów
class MovesTree:
    def __init__(self, turn, alpha, beta, val, board, poss):
        self.turn = turn
        self.alpha = alpha
        self.beta = beta
        self.val = val
        self.board = copy.deepcopy(board)
        self.poss = copy.deepcopy(poss)
        self.children = []

    def valid(self, x, y):
        return 0 <= x <= 7 and 0 <= y <= 7 and self.board[x][y] == empty
    
    def generate_moves(self):
        poss_moves = []
        for u in self.poss[self.turn]:
            for i, j in vector_moves:
                pos = [u[0] + i, u[1] + j]
                zbity = False
                while 0 <= pos[0] <= 7 and 0 <= pos[1] <= 7 and self.board[pos[0]][pos[1]] == self.turn ^ 1:
                    zbity = True
                    pos[0] += i
                    pos[1] += j
                if self.valid(pos[0], pos[1]) and zbity:
                    poss_moves.append(pos)
        return poss_moves
    
    def make_move(self, x, y):
        player = self.turn
        self.board[x][y] = player
        self.poss[player].append([x, y])
        
        for i, j in vector_moves:
            pos = [x + i, y + j]
            to_flip = []
            while 0 <= pos[0] <= 7 and 0 <= pos[1] <= 7 and self.board[pos[0]][pos[1]] == player ^ 1:
                to_flip.append([pos[0], pos[1]])
                pos[0] += i
                pos[1] += j
            if 0 <= pos[0] <= 7 and 0 <= pos[1] <= 7 and self.board[pos[0]][pos[1]] == player:
                for fx, fy in to_flip:
                    self.board[fx][fy] = player
                    self.poss[player].append([fx, fy])
                    self.poss[player ^ 1].remove([fx, fy])
    
    def eval(self):
        return len(self.poss[self.turn]) - len(self.poss[self.turn ^ 1])
    
    def game_result(self):
        black_count = sum(row.count(black) for row in self.board)
        white_count = sum(row.count(white) for row in self.board)
        return 0 if black_count > white_count else 1

def min_max(node, depth):
    if depth == 8 or not node.generate_moves():
        return node.eval()
    
    if node.turn == max_player:
        value = float('-inf')
        for move in node.generate_moves():
            child = MovesTree(node.turn ^ 1, node.alpha, node.beta, float('inf'), node.board, node.poss)
            child.make_move(*move)
            node.children.append(child)
            value = max(value, min_max(child, depth + 1))
            node.alpha = max(node.alpha, value)
            if node.alpha >= node.beta:
                break
        return value
    else:
        value = float('inf')
        for move in node.generate_moves():
            child = MovesTree(node.turn ^ 1, node.alpha, node.beta, float('-inf'), node.board, node.poss)
            child.make_move(*move)
            node.children.append(child)
            value = min(value, min_max(child, depth + 1))
            node.beta = min(node.beta, value)
            if node.beta <= node.alpha:
                break
        return value

def choose_optimal(node):
    if node.turn == max_player:
        return max(node.children, key=lambda child: child.val, default=None)
    else:
        return min(node.children, key=lambda child: child.val, default=None)

def choose_random(node):
    return random.choice(node.children) if node.children else None

if __name__ == "__main__":
    result = [0, 0]
    for _ in range(1000):
        # Inicjalizacja planszy
        board = [[empty] * 8 for _ in range(8)]
        board[3][3] = board[4][4] = black
        board[3][4] = board[4][3] = white
        
        # Inicjalizacja węzła początkowego
        black_poss = [[3, 3], [4, 4]]
        white_poss = [[3, 4], [4, 3]]
        moves_tree = MovesTree(black, float('-inf'), float('inf'), float('-inf'), board, [black_poss, white_poss])
        
        end_game = False
        turn = black
        turn_no = 1
        
        while not end_game:
            if turn == black:
                min_max(moves_tree, 0)
                new_moves_tree = choose_optimal(moves_tree)
            else:
                if turn_no == 1:
                    min_max(moves_tree, 0)
                new_moves_tree = choose_random(moves_tree)
            
            if new_moves_tree is None:
                end_game = True
                break
            
            moves_tree = new_moves_tree
            turn ^= 1
            turn_no += 1
            
            if not moves_tree.generate_moves():
                end_game = True

        result[moves_tree.game_result()] += 1
        print(result)
