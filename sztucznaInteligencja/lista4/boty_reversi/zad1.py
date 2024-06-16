import random
import copy

max_tree_deep = 7
vis_board = set()
black, white, empty = range(3)
max_player, min_player = black, white
end_game = False
vector_moves = [[i, j] for i in [-1, 0, 1] for j in [-1, 0, 1] if (i, j) != (0, 0)]

class Moves_tree:
    def valid(self, x, y):
        return 0 <= x <= 7 and 0 <= y <= 7 and self.board[x][y] == empty
    
    def __init__(self, turn, alpha, beta, val, board, poss):
        self.turn = turn
        self.val = val
        self.alpha = alpha
        self.beta = beta
        self.board = copy.deepcopy(board)
        self.poss = copy.deepcopy(poss)
        self.children = []
    
    def generate_moves(self):
        poss_moves = []
        for u in self.poss[self.turn]:
            for i in [-1, 0, 1]:
                for j in [-1, 0, 1]:
                    if [i, j] == [0, 0]: continue
                    pos = [u[0] + i, u[1] + j]
                    zbity = False
                    
                    while 0 <= pos[0] <= 7 and 0 <= pos[1] <= 7 and self.board[pos[0]][pos[1]] == self.turn ^ 1:
                        zbity = True
                        pos[0] += i; pos[1] += j
                        
                    if 0 <= pos[0] <= 7 and 0 <= pos[1] <= 7 and self.board[pos[0]][pos[1]] == empty and zbity:
                        poss_moves.append(pos)        
        return poss_moves
    
    def make_move(self, x, y):
        player = self.turn ^ 1
        self.board[x][y] = player
        self.poss[player].append([x, y])
        
        for i in [-1, 0, 1]:
            for j in [-1, 0, 1]:
                if [i, j] == [0, 0]: 
                    continue
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
    
    def print(self):
        for i in range(8):
            for j in range(8):
                if self.board[i][j] == empty: print('.', end='')
                elif self.board[i][j] == black: print('B', end='')
                else: print('W', end='')
            print()
        print()
                
    def eval(self):
        self.val = len(self.poss[self.turn]) - len(self.poss[self.turn^1])
        return self.val
    
    def game_result(self):
        return 0 if len(self.poss[0]) > len(self.poss[1]) else 1

# do debugu
def deep_of_tree(moves_tree, deep):
    maxi = deep
    for u in moves_tree.children:
        maxi = deep_of_tree(u, deep + 1)
    
    return maxi

def sajz_of_tree(moves_tree: Moves_tree):
    sajz = 1
    for u in moves_tree.children:
        sajz += sajz_of_tree(u)
    
    return sajz
    
def min_max(moves_tree: Moves_tree, deep: int):
    player = moves_tree.turn
    if deep >= max_tree_deep:
        return moves_tree.eval()
    
    # jeśli nie ma dzieci 
    if moves_tree.children == []:
        generated_moves = moves_tree.generate_moves()
        
        # jeśli to już koniec
        if generated_moves == []:
            return moves_tree.eval()
        
        # to nie jest koniec więc robie dzieci 
        for [x, y] in generated_moves:
            new_moves_tree = Moves_tree(player^1, moves_tree.alpha, moves_tree.beta, (float('-inf') if player == max_player else float('inf')), moves_tree.board, moves_tree.poss)
            moves_tree.children.append(new_moves_tree)
            new_moves_tree.make_move(x, y)
            
            # sprawdzenie czy się nie powtarzamy 
            tuples = tuple(tuple(line) for line in new_moves_tree.board)
            if hash(tuples) in vis_board:
                moves_tree.children.pop()
            vis_board.add(hash(tuples))
            
            # teraz new_moves_tree jest już gotowe moge robić dla niego min_max
            if player == max_player:
                new_moves_tree.val = min_max(new_moves_tree, deep + 1)
                moves_tree.val = max(moves_tree.val, new_moves_tree.val)
                moves_tree.alpha = max(moves_tree.alpha, new_moves_tree.val)
                if moves_tree.beta <= moves_tree.alpha:
                    break
            
            else:
                new_moves_tree.val = min_max(new_moves_tree, deep + 1)
                moves_tree.val = min(moves_tree.val, new_moves_tree.val)
                moves_tree.beta = min(moves_tree.beta, new_moves_tree.val)
                if moves_tree.beta <= moves_tree.alpha:
                    break
                
    # jeśli ma dzieci
    else:
        for child in moves_tree.children:
            if moves_tree.beta <= moves_tree.alpha:
                break
            if player == max_player:
                min_max(child, deep + 1)
                moves_tree.val = max(moves_tree.val, child.val)
                moves_tree.alpha = max(moves_tree.alpha, child.val)
            else:
                min_max(child, deep + 1)
                moves_tree.val = min(moves_tree.val, child.val)
                moves_tree.beta = min(moves_tree.beta, child.val)
                
    return moves_tree.val
    
    # if player == max_player:
    #     if moves_tree.children != []:
    #         best = None
    #         for child in moves_tree.children:
    #             if best == None or child.val > best.val:
    #                 best = child
    #         return min_max(best, deep + 1)
    #     else:
    #         generated_moves = moves_tree.generate_moves()
    #         if generated_moves == []:
    #             return moves_tree.eval()
                
    #         for [x, y] in generated_moves:
    #             new_moves_tree = Moves_tree(min_player, moves_tree.alpha, moves_tree.beta, float('inf'), moves_tree.board, moves_tree.poss)
    #             moves_tree.children.append(new_moves_tree)
    #             new_moves_tree.make_move(x, y)
                
    #             new_moves_tree.val = min_max(new_moves_tree, deep + 1)
    #             moves_tree.val = max(moves_tree.val, new_moves_tree.val)
    #             moves_tree.alpha = max(moves_tree.alpha, new_moves_tree.val)
    #             if moves_tree.beta <= moves_tree.alpha:
    #                 break
                
    #         return moves_tree.val
    
    # if player == min_player:
    #     if moves_tree.children != []:
    #         best = None
    #         for child in moves_tree.children:
    #             if best == None or child.val < best.val:
    #                 best = child
    #         return min_max(best, deep + 1)
    #     else:
    #         generated_moves = moves_tree.generate_moves()
    #         if generated_moves == []:
    #             return moves_tree.eval()
            
    #         for [x, y] in generated_moves:
    #             new_moves_tree = Moves_tree(max_player, moves_tree.alpha, moves_tree.beta, float('-inf'), moves_tree.board, moves_tree.poss)
    #             moves_tree.children.append(new_moves_tree)
    #             new_moves_tree.make_move(x, y)
                
    #             new_moves_tree.val = min_max(new_moves_tree, deep + 1)
    #             moves_tree.val = min(moves_tree.val, new_moves_tree.val)
    #             moves_tree.beta = min(moves_tree.beta, new_moves_tree.val)
    #             if moves_tree.beta <= moves_tree.alpha:
    #                 break
                
    #         return moves_tree.val
        
def choose_optimal(moves_tree):
    new_moves_tree = None
    if moves_tree.turn == max_player:
        for child in moves_tree.children:
            if new_moves_tree == None or child.val > new_moves_tree.val:
                new_moves_tree = child
                
    if moves_tree.turn == min_player:
        for child in moves_tree.children:
            if new_moves_tree == None or child.val < new_moves_tree.val:
                new_moves_tree = child
    
    return new_moves_tree
    
def choose_random(moves_tree):
    return random.choice(moves_tree.children)
    
if __name__ == "__main__":
    result = [0, 0]
    for i in range(1000): 
        #stwurz plansze
        board = [[empty] * 8 for _ in range(8)]
        board[3][3] = board[4][4] = black
        board[3][4] = board[4][3] = white
        
        #zacznij tworzyć drzewo
        player = [black, white]
        
        black_poss = [[3,3], [4,4]]
        white_poss = [[3,4], [4,3]]
        
        moves_tree = Moves_tree(black, float('-inf'), float('inf'), (float('-inf') if player[0] == max_player else float('inf')), board, [black_poss, white_poss])
        end_game = False
        vis_board = set()
        
        turn = black
        tree_deep = 0
        
        while(not end_game):
            if turn == black:
                min_max(moves_tree, tree_deep)
                if(moves_tree.children == []):
                    break

                moves_tree = choose_optimal(moves_tree)
                tree_deep = max_tree_deep - 1
            else:
                if tree_deep == 0:
                    min_max(moves_tree, tree_deep)
                if(moves_tree.children == []):
                    break
                moves_tree = choose_random(moves_tree)
                tree_deep -= 1
            
            turn ^= 1
            # moves_tree.print() # debug

        result[moves_tree.game_result()] += 1
        print(result)