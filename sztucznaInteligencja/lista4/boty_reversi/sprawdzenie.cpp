#include <bits/stdc++.h>
using namespace std;

enum {black, white, blank};
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
int max_tree_deep = 3;
const int inf = 1e9 + 7;
const int max_player = black;
const int min_player = white;
 
struct State{
    vvi board;
    int deep;
    int player;
    int alfa;
    int beta;
    int val;
    vector<pii> black_poss;
    vector<pii> white_poss;
};
 
 
void set_initial_state(State &state, int player){
    state.board.resize(8);
    for(int i = 0; i < 8; i++){
        state.board[i].resize(8);
        for(int j = 0; j < 8; j++)
            state.board[i][j] = blank;
    }
 
    state.board[3][3] = state.board[4][4] = black;
    state.board[3][4] = state.board[4][3] = white;
    state.black_poss.push_back({3, 3});
    state.black_poss.push_back({4, 4});
    state.white_poss.push_back({3, 4});
    state.white_poss.push_back({4, 3});
    
    state.deep = 0;
    state.player = player;
    state.alfa = -inf;
    state.beta = inf;
    state.val = (player == max_player ? -inf : inf);
}
 
bool valid_coord(const pii &poss){
    return 0 <= poss.first && poss.first < 8 && 0 <= poss.second && poss.second < 8;
}
 
void make_move(State &child, const pii &move){
    //zmiana na chwile 
    child.player ^= 1;
 
    const int &x = move.first, &y = move.second;
    vector<pii> &my_poss = (child.player == black ? child.black_poss : child.white_poss);
    vector<pii> &his_poss = (child.player == black ? child.white_poss : child.black_poss);
 
    child.board[x][y] = child.player;
    my_poss.push_back(move);
 
    for(int i: {-1, 0, 1}){
        for(int j: {-1, 0, 1}){
            if(!i && !j) continue;
            pii poss = {x + i, y + j};
            vector<pii> to_flip;
 
            while(valid_coord(poss) && child.board[poss.first][poss.second] == child.player ^ 1){
                to_flip.push_back(poss);
                poss.first += i, poss.second += j;
            }
 
            if(valid_coord(poss) && child.board[poss.first][poss.second] == child.player){
                for(auto [a, b]: to_flip){
                    child.board[a][b] = child.player;
                    my_poss.push_back({a, b});
                    auto rm = find(his_poss.begin(), his_poss.end(), make_pair(a, b));
 
                    if(rm != his_poss.end()) his_poss.erase(rm);
                }
            }
        }
    }
 
    child.player ^= 1;
}
 
void make_child_from_state(const State &state, State &child, const pii &move){
    child.board = state.board; // to jest kopia
    child.deep = state.deep + 1;
    child.player = state.player ^ 1;
    child.alfa = state.alfa;
    child.beta = state.beta;
    child.val = (child.player == max_player ? -inf : inf); 
    child.black_poss = state.black_poss;
    child.white_poss = state.white_poss;
 
    make_move(child, move);
}
 
int eval_state(const State &state){
    // return state.black_poss.size() - state.white_poss.size();
    const vector<vector<int>> val = {
       {4,0,2,2,2,2,0,4}, 
       {0,0,2,1,1,2,0,0}, 
       {2,2,2,1,1,2,2,2}, 
       {2,1,1,1,1,1,1,2}, 
       {2,1,1,1,1,1,1,2}, 
       {2,2,2,1,1,2,2,2}, 
       {0,0,2,1,1,2,0,0}, 
       {4,0,2,2,2,2,0,4}, 
    };

    int b = 0, w = 0;
    for(auto [x, y]: state.black_poss)
        b += val[x][y];
    for(auto [x, y]: state.white_poss)
        w += val[x][y];
    
    return b - w;
}
 
 
vector<pii> generate_moves(const State &state){
    vector<pii> possible_moves;
    for(auto u: (state.player == black ? state.black_poss : state.white_poss)){
        for(int i: {-1, 0, 1}){
            for(int j: {-1, 0, 1}){
                if(!i and !j) continue;
                pii poss = {u.first + i, u.second + j};
                bool captured = false;
 
                while(valid_coord(poss) && state.board[poss.first][poss.second] == (state.player ^ 1))
                    captured = true, poss.first += i, poss.second += j;
 
                if(valid_coord(poss) && state.board[poss.first][poss.second] == blank && captured)
                    possible_moves.push_back(poss);
            }
        }
    }
 
    return possible_moves;
}
 
State min_max(State state){
    // sprawdzanie czy można grać 
    if(state.deep >= max_tree_deep){
        state.val = eval_state(state);
        return state;
    }
 
    vector<pii> possible_moves = generate_moves(state);
    if(possible_moves.size() == 0){
        state.val = eval_state(state);
        return state;
    }
 
    // moge grać 
    for(const auto move: possible_moves){
        State child; make_child_from_state(state, child, move);
        child = min_max(child);
        
        if(state.player == max_player){
            state.val = max(state.val, child.val);
            state.alfa = max(state.alfa, state.val);
 
            if(state.val >= state.beta)
                break;
        }
        else if(state.player == min_player){
            state.val = min(state.val, child.val);
            state.beta = min(state.beta, state.val);
            if(state.val <= state.alfa)
                break;
        }
    }
 
    return state;
}
 
State choose_random(const State &state){
    vector<pii> possible_moves = generate_moves(state);
    int idx = rand() % possible_moves.size();
    State child; make_child_from_state(state, child, possible_moves[idx]);
    return child;
}
 
long seed()
{
    auto t=chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
}
 
int eval_end_board(State state){
        return state.black_poss.size() > state.white_poss.size();
}

// czy a jest lepszy od b
bool cmp(const State &a, const State &b){
    return eval_state(a) > eval_state(b);
}
 
State choose_smart(State state){
    State best_child;
    vector<pii> possible_moves = generate_moves(state); 
    vector<State> children;
    for(auto move: possible_moves){
        State child; make_child_from_state(state, child, move);
        children.push_back(child);
    }

    // sort(children.begin(), children.end(), cmp);
 
    for(auto child: children){
        child = min_max(child);
        
        if(state.player == max_player){
            if(child.val > state.val){
                state.val = child.val;
                best_child = child;
            }
 
            state.alfa = max(state.alfa, state.val);
            if(state.val >= state.beta)
                break;
        
        }
        else if(state.player == min_player){
            if(child.val < state.val){
                state.val = child.val;
                best_child = child;
            }
 
            state.beta = min(state.beta, state.val);
            if(state.val <= state.alfa)
                break;
        }
    }
 
    return best_child;
}

void tidy_state(State &state){
    state.deep = 0;
    state.alfa = -inf;
    state.beta = inf;
    state.val = (state.player == max_player ? -inf : inf);
}
 
// debug
void print_board(const State state); 

int main(){    
    srand(seed());
    pii score = {0, 0};
    for(int i = 0; i < 1000; i++){
 
        // ustawianie gry
        State state;
        set_initial_state(state, black);
        int stranting_player = rand() % 2;
 
        // gra dopuki ktoś nie wygra
        int cnt = 0;
        for(int turn = stranting_player; !generate_moves(state).empty(); turn ^= 1){
            if(turn == max_player)
                state = choose_smart(state);
            else
                state = choose_random(state);

            tidy_state(state);
            cnt++;
            if(cnt == 4 && max_tree_deep < 5) cnt = 0, max_tree_deep++;

            // debug
            // cout << visited << endl; visited = 0;
            // print_board(state); //debug
        }
        max_tree_deep = 2;
        
 
        if(eval_end_board(state) == stranting_player) score.first += 1;
        else score.second += 1;
        cout << "black: " << score.first << " white: " << score.second << endl;
    }
}
 
void print_board(const State state){
    cout << (state.player == black ^ 1 ? "black" : "white") << endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++)
            if(state.board[i][j] == black) cout << 'B' << ' ';
            else if(state.board[i][j] == white) cout << 'W' << ' ';
            else cout << '.' << ' ';
        cout << endl;
    }
    cout << endl;
}