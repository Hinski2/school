import chess
import random

max_player, min_player = True, False
max_deep = 2

def material_sum(board: chess.Board, color) -> int:
    ans = 0
    ans += 1 * len(board.pieces(chess.PAWN, color))
    ans += 3 * len(board.pieces(chess.KNIGHT, color))
    ans += 3 * len(board.pieces(chess.BISHOP, color))
    ans += 5 * len(board.pieces(chess.ROOK, color))
    ans += 9 * len(board.pieces(chess.QUEEN, color))
    ans += 1000 * len(board.pieces(chess.KING, color))
    return ans

def dist_between(p1, p2):
    p1 = (p1 // 8, p1 % 8)
    p2 = (p2 // 8, p2 % 8)
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

def check_for_king_threat(board: chess.Board, color):
    # sprawdzam czy dla króla color jest zagrożenie ze storny pionków color^1
    enemy_poss = []
    for piece in chess.PIECE_TYPES:
        enemy_poss += list(board.pieces(piece, color^1))
    
    king_poss = board.king(color)
    dist = 0
    for poss in enemy_poss:
        dist += dist_between(king_poss, poss)
        
    return dist

def check_pawn_cover(board: chess.Board, color):
    poss_list = []
    for piece in chess.PIECE_TYPES:
        poss_list += list(board.pieces(piece, color))
    
    no_of_coverd = 0   
    if color == chess.WHITE:
       for poss in poss_list:
           if poss - 9 < 0: continue
           if (poss % 8 != 0 and board.piece_at(poss - 9) != None) or (poss % 8 != 7 and board.piece_at(poss - 7) != None):
               no_of_coverd += 1
    else:
       for poss in poss_list:
           if poss + 9 > 63: continue
           if (poss % 8 != 0 and board.piece_at(poss + 9) != None) or (poss % 8 != 7 and board.piece_at(poss + 7) != None):
               no_of_coverd += 1
               
    return no_of_coverd

def pawn_distance_from_edge(board: chess.Board, color):
    poss_list = list(board.pieces(chess.PAWN, color))
    dist = 0
    for poss in poss_list:
        x_coord = poss // 8
        if color == chess.WHITE:
            dist += x_coord #im bliżej ściany tym lepiej 
        else:
            dist += 7 - x_coord
    return dist

def center_control(board, color):
    poss_list = []
    for piece in chess.PIECE_TYPES:
        poss_list += list(board.pieces(piece, color))
        
    ans = 0
    for poss in poss_list:
        x_coord = poss // 8
        if color == chess.WHITE and x_coord < 6:
            ans += 1 
        elif color == chess.BLACK and x_coord > 1:
            ans += 1
            
    return ans

def heura(board: chess.Board) -> int:
    ans = 0
    # sprawdzenie przewagi materialnej
    ans += material_sum(board, max_player) - material_sum(board, min_player)
    
    # sprawdzenie ruchliwości 
    ans += len(list(board.legal_moves)) * (-1 if board.turn != max_player else 1)
    board.turn = not board.turn
    ans += len(list(board.legal_moves)) * (-1 if board.turn != max_player else 1)
    board.turn = not board.turn
    
    # sprawdzeni zagrożania dla króla
    ans -= check_for_king_threat(board, max_player) 
    ans += check_for_king_threat(board, min_player)
    
    # sprawdzenie czy pionki są kryte przez inne 
    ans += check_pawn_cover(board, max_player)
    ans -= check_pawn_cover(board, min_player)
    
    # opłaca się dojść do końca zwykłymi pionkami i je zamienić na lepsze figury
    ans += pawn_distance_from_edge(board, max_player)
    ans -= pawn_distance_from_edge(board, min_player)
    
    # kontrala środka
    ans += center_control(board, max_player)
    ans -= center_control(board, min_player)
        
    return ans

def do_move(board: chess.Board):
    global max_player, min_player
    max_player = board.turn
    min_player = False if max_player else True
    
    best_move = [None, float('-inf')]
    legal_moves = board.legal_moves
    for move in legal_moves:
        #robie ruch
        board.push(move)
        
        #jestem max_playerem, więc on jest min
        val = min_max(board, max_player, max_deep - 1)
        if val > best_move[1]:
            best_move = [board.copy(), val]
        
        # usuwamy ostatni ruch
        board.pop()
    
    return best_move[0] #zwracam next_board

def min_max(board: chess.Board, player: int, deep: int) -> float:
    # to koniec gry
    if(deep == 0 or board.is_game_over()):
        return heura(board)
    
    # to jeszcze nie koniec gry 
    player ^= 1
    best_move = float('-inf') if player == max_player else float('inf')
    legal_moves = board.legal_moves
    for move in legal_moves:
        # robie ruch
        board.push(move)
        
        # jeśli to max_player
        if player == max_player:
            val = min_max(board, player, deep - 1)
            if val > best_move:
                best_move = val
            
        # jeśli to min_player
        else:
            val = min_max(board, player, deep - 1)
            if val < best_move:
                best_move = val
                
        #usuwamy ostatni ruch
        board.pop()
    
    return best_move

def random_move(board: chess.Board):
    legal_moves = list(board.legal_moves)
    board.push(random.choice(legal_moves))
    return board

def main():
    score = [0, 0] #white, black
    for _ in range(100):
        board = chess.Board() 
        
        who_starts = 0 # jeśli jeden to jako biały gra mądry bot, a jako random gra czarny
        move = who_starts
        while(not board.is_game_over()):
            # wykonanie ruchu
            if move:
                board = do_move(board)
            else:
                board = random_move(board) 
            
            move ^= 1 
            print(board)
            print(f"white score = {score[0]}, black score = {score[1]}\n")
        
        # zmiana wyniku
        if board.turn == chess.WHITE: score[1] += 1
        else: score[0] += 1
    

if __name__ == "__main__":
    main()