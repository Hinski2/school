#include <iostream>
#include <vector>
#include <limits>
 
enum class Sign { black, white, empty };
static const short SIZE = 8;
static const short DEPTH = 3;
static const short GAMES = 1000;
 
struct Move {
    std::pair<short, short> cord;
    std::vector<std::pair<short, short>> directs;
};
 
class Board {
    public:
        Sign board[SIZE][SIZE];
 
        Board() {
            for (short i = 0; i < SIZE; i++) {
                for (short j = 0; j < SIZE; j++) {
                    board[i][j] = Sign::empty;
                }
            }
 
            board[3][3] = board[4][4] = Sign::white;
            board[3][4] = board[4][3] = Sign::black;
            return;
        }
 
    void print() {
        for (short i = 0; i < SIZE; i++) {
            for (short j = 0; j < SIZE; j++) {
                if (board[i][j] == Sign::empty) {
                    std::cout << " . ";
                }
                else if (board[i][j] == Sign::black) {
                    std::cout << " B ";
                }
                else if (board[i][j] == Sign::white) {
                    std::cout << " W ";
                }
            }
            std::cout << std::endl;
        }
 
        std::cout << std::endl;
        return;
    }
};
 
std::vector<Move> gen_moves(const Board& board, Sign player);
Sign not_player(Sign player);
void make_move(Board& board, Move move, Sign player);
 
struct Node {
    Board board;
    Sign to_move;
    std::vector <Node*> children;
 
    Node(Board b, Sign player) : board(b), to_move(player) {}
 
    ~Node() {
        for (Node* child: children) {
            delete child;
        }
    }
 
    bool gen_children() {
        std::vector<Move> moves = gen_moves(board, to_move);
        Sign opposite = not_player(to_move);
 
        if (moves.empty()) {
            if (children.empty()) {
                children.resize(1, nullptr);
                children[0] = new Node(board, opposite);
            }
 
            return false;
        }
        else {
            if (children.empty()) {
                children.resize(moves.size(), nullptr);
 
                for (int i = 0; i < moves.size(); i++) {
                    Board new_board = board;
                    make_move(new_board, moves[i], to_move);
                    children[i] = new Node(new_board, opposite);
                }
            }
 
            return true;
        }
    }
};
 
bool in_bounds(short x, short y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return false;
    }
 
    return true;
}
 
Sign not_player(Sign player) {
    return player == Sign::black ? Sign::white : Sign::black;
}
 
std::vector<std::pair<short, short>> valid_move(const Board& board, short i, short j, Sign player, Sign opposite) {
    std::vector<std::pair<short, short>> res;
 
    if (board.board[i][j] == Sign::empty) {
        // jesli pusty punkt towarzyszy przeciwnemu kolorowi
        // i da sie z niego dojsc do naszego, to dodajemy go
        for (short dx : {-1, 0, 1}) {
            for (short dy : {-1, 0, 1}) {
                short new_x = i + dx;
                short new_y = j + dy;
 
                if (in_bounds(new_x, new_y) && board.board[new_x][new_y] == opposite) {
                    while (true) {
                        new_x += dx;
                        new_y += dy;
 
                        if (in_bounds(new_x, new_y)) {
                            Sign cell = board.board[new_x][new_y];
 
                            if (cell == player) {
                                res.push_back({dx, dy});
                            }
                            else if (cell == Sign::white) {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
 
    return res;
}
 
std::vector<Move> gen_moves(const Board& board, Sign player) {
    std::vector<Move> res;
    Sign opposite = not_player(player);
 
    for (short i = 0; i < SIZE; i++) {
        for (short j = 0; j < SIZE; j++) {
            std::vector<std::pair<short, short>> move_dirs = valid_move(board, i, j, player, opposite);
 
            if (move_dirs.size() > 0) {
                res.push_back({{i, j}, move_dirs});
            }
        }
    }
    
    return res;
}
 
 
void make_move(Board& board, Move move, Sign player) {
    Sign opposite = not_player(player);
 
    board.board[move.cord.first][move.cord.second] = player;
 
    for (const auto& [dx, dy] : move.directs) {
        short x = move.cord.first;
        short y = move.cord.second;
 
        x += dx;
        y += dy;
 
        while(in_bounds(x, y) && board.board[x][y] == opposite) {
            board.board[x][y] = player;
        }
    }
 
    return;
}
 
int eval(const Board& board, Sign player) {
    int score = 0;
 
    for (short i = 0; i < SIZE; i++) {
        for (short j = 0; j < SIZE; j++) {
            Sign cell = board.board[i][j];
 
            if (cell == player) {
                score++;
            }
            else if (cell != Sign::empty) {
                score--;
            }
        }
    }
 
    return score;
}
 
int minimax(Node* node, short depth, bool maximizing, int alpha, int beta) {
    if (node->children.empty()) {
        node->gen_children();
    }
 
    if (depth == 0) {
        return eval(node->board, not_player(node->to_move));
    }
 
    if (maximizing) {
        int max_eval = std::numeric_limits<int>::min();
 
        for (Node* child : node->children) {
            if (!child) {
                continue;
            }
 
            int eval = minimax(child, depth - 1, false, alpha, beta);
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);
 
            if (beta <= alpha) {
                break;
            }
        }
 
        return max_eval;
    }
    else {
        int min_eval = std::numeric_limits<int>::max();
 
        for (Node* child : node->children) {
            if (!child) continue;
 
            int eval = minimax(child, depth - 1, true, alpha, beta);
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);
 
            if (beta <= alpha) {
                break;
            }
        }
 
        return min_eval;
    }
}
 
Node* random_move(Node* root) {
    return root->children[rand() % root->children.size()];
}
 
Node* best_move(Node* root) {
    int best_value = std::numeric_limits<int>::min(), node_val;
    Node* best_node = nullptr;
 
    for (Node* child : root->children) {
        if (!child) {
            continue;
        }
 
        node_val = minimax(child, DEPTH, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
 
        if (node_val > best_value) {
            best_value = node_val;
            best_node = child;
        }
    }
 
    return best_node;
}
 
int main(int argc, char *argv[])
{
    Board board;
    Node* starting;
    Node* root;
    Node* best_node = nullptr;
    bool possible = false, skipped = false;
    std::pair<short, short> wins = {0, 0};
 
    srand(time(NULL));
    
    for (int i = 0; i < GAMES; i++) {
        root = new Node(board, Sign::black);
        starting = root;
 
        while (true) {
            possible = root->gen_children();
 
            if (!possible) {
                if (skipped) {
                    if (eval(root->board, Sign::black)) {
                        wins.first++;
                    }
                    else {
                        wins.second++;
                    }
                    break;
                }
 
                skipped = true;
            }
            else {
                skipped = false;
            }
 
            if (root->to_move == Sign::black) {
                best_node = best_move(root);
            }
            else {
                best_node = random_move(root);
            }
            
            if (best_node) {
                root = best_node;
                // root->board.print();
            }
            else {
                std::cout << "No valid moves left" << std::endl;
                break;
            }
        }
 
        std::cout << "Minimax #wins: " << wins.first << " Random #wins: " << wins.second << std::endl;
        delete starting;
    }
 
    return 0;
}