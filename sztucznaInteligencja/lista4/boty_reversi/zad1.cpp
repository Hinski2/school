#include<bits/stdc++.h>
using namespace std;

enum {black, white, blank};
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;
const int max_tree_deep = 5;
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
    vector<State*> children;
    vector<pii> black_poss;
    vector<pii> white_poss;
};

// robienie ruchu
void smart_choose(State &state);
void random_choose(State &state);
void min_max(State &state);

// ogarnianie drzewa
void make_move(State &child, const pii &move);
void make_step(State &state, State *child);
void rm(State *state);
void set_initial_state(State &state, int player);
void tidy_state(State &state);

// funkcje pomocnicze
bool valid_coord(const pii &poss);
void make_child_from_state(const State &state, State &child, const pii &move);
int eval_state(const State &state);
vector<pii> generate_moves(const State &state);
int eval_end_board(State state);
long seed();

// debug
void print_board(const State state);
int deep(const State state);
int sajz(const State v);

// hasze
unordered_set<ll> hsh_set;
ll make_hsh(const State &state);

int main(){    
    srand(seed());
    pii score = {0, 0};
    for(int i = 0; i < 1000; i++){

        // ustawianie gry
        State state;
        set_initial_state(state, black);

        // gra dopuki ktoś nie wygra
        for(int turn = 0; !generate_moves(state).empty(); turn ^= 1){
            if(turn == black)
                smart_choose(state);
            else
                random_choose(state);
            
            tidy_state(state);  

            // cout << deep(state) << endl; //debug
            // print_board(state); //debug
            // cout << sajz(state) << endl;
        }

        hsh_set.clear();
        if(eval_end_board(state) == black) score.first += 1;
        else score.second += 1;
        cout << "black: " << score.first << " white: " << score.second << endl;
    }
}

ll make_hsh(const State &state){
    const ll p = 179;
    const ll q = 313;
    const ll mod = 1e9 + 7;
    ll hsh = 0;
    for(ll i = 0, x = p; i < 8; i++, x *= p, x %= mod)
        for(ll j = 0, y = q; j < 8; j++, y *= q, y %= mod)
            hsh += (state.board[i][j] * x * y) % mod, hsh %= mod;
    return hsh;
}

int sajz(const State v){
    int s = 1;
    for(auto u: v.children)
        s += sajz(*u);
    return s;
}

int deep(const State v){
    int d = 1;
    for(auto u: v.children)
        d = max(d, deep(*u) + 1);
    return d;
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

void rm(State *state){
    for(auto child: state -> children)
        rm(child);

    hsh_set.erase(make_hsh(*state));
    state->children.clear(); 
    delete state;
}

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

void tidy_state(State &state){
    state.deep = 0;
    state.alfa = -inf;
    state.beta = inf;
    state.val = (state.player == max_player ? -inf : inf);
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
    int black = state.black_poss.size() + (state.board[0][0] == black + state.board[0][7] == black + state.board[7][0] == black + state.board[7][7] == black) * 0;
    int white = state.white_poss.size() + (state.board[0][0] == white + state.board[0][7] == white + state.board[7][0] == white + state.board[7][7] == white) * 0;
    return black - white;
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
    
void make_step(State &state, State *child){
    for(auto u: state.children)
        if(u != child) rm(u);
    
    state.children.clear();
    hsh_set.erase(make_hsh(state));
    state = *child;
}

void min_max(State &state){
    // sprawdzanie czy można grać 
    if(state.deep >= max_tree_deep){
        state.val = eval_state(state);
        return;
    }

    // jeśli jeszcze nie tworzyłem dzieci dla state
    if(state.children.empty() ){
        // to już koniec nie moge robić dzeci 
        vector<pii> possible_moves = generate_moves(state);
        if(possible_moves.size() == 0){
            state.val = eval_state(state);
            return;
        }

        // moge grać 
        for(const auto move: possible_moves){
            State* child = new(State);
            make_child_from_state(state, *child, move);
            ll hsh = make_hsh(*child);
            if(hsh_set.count(hsh) == 0){
                state.children.push_back(child);
                hsh_set.insert(hsh);
            }
        }

        if(state.children.empty()){
            state.val = eval_state(state);
            return;
        }

        for(auto child: state.children){
            min_max(*child);
            
            if(state.player == max_player){
                state.val = max(state.val, child -> val);
                state.alfa = max(state.alfa, state.val);

                if(state.beta <= state.alfa)
                    break;
            }
            else if(state.player == min_player){
                state.val = min(state.val, child -> val);
                state.beta = min(state.beta, state.val);
                if(state.beta <= state.alfa)
                    break;
            }
        }
    }
    // już miałem dzieci 
    else{
        for(auto child: state.children){
            child -> deep = state.deep + 1;
            child -> alfa = state.alfa;
            child -> beta = state.beta;
            child -> val = (child -> player == max_player ? -inf : inf);

            min_max(*child);
            if(state.player == max_player){
                state.val = max(state.val, child -> val);
                state.alfa = max(state.alfa, state.val);

                if(state.beta <= state.alfa)
                    break;
            }
            else if(state.player == min_player){
                state.val = min(state.val, child -> val);
                state.beta = min(state.beta, state.val);
                if(state.beta <= state.alfa)
                    break;
            }
        }
    }
}

void random_choose(State &state){
    if(state.children.empty()){
        vector<pii> possible_moves = generate_moves(state);

        // moge grać 
        for(const auto move: possible_moves){
            State* child = new(State);
            state.children.push_back(child);
            make_child_from_state(state, *child, move);
        }
    }
        
    int idx = rand() % state.children.size();
    State *child = state.children[idx];
    make_step(state, child);
}

long seed()
{
    auto t=chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
}

int eval_end_board(State state){
    if(state.black_poss.size() > state.white_poss.size()) return black;
    return white;
}

void smart_choose(State &state){
    // jeśli jeszcze nie tworzyłem dzieci dla state
    if(state.children.empty()){
        vector<pii> possible_moves = generate_moves(state);
        for(const auto move: possible_moves){
            State* child = new(State);
            make_child_from_state(state, *child, move);
            ll hsh = make_hsh(*child);
            if(hsh_set.count(hsh) == 0){
                state.children.push_back(child);
                hsh_set.insert(hsh);
            }
        }
    }

    // już miałem dzieci 
    State *best_child;
    vector<pii> possible_moves = generate_moves(state); 

    for(auto child: state.children){
        child -> deep = state.deep + 1;
        child -> alfa = state.alfa;
        child -> beta = state.beta;
        child -> val = (child -> player == max_player ? -inf : inf);

        min_max(*child);
        
        if(state.player == max_player){
            if(child -> val > state.val){
                state.val = child -> val;
                best_child = child;
            }

            state.alfa = max(state.alfa, state.val);
            if(state.beta <= state.alfa)
                break;
        
        }
        else if(state.player == min_player){
            if(child -> val < state.val){
                state.val = child -> val;
                best_child = child;
            }

            state.beta = min(state.beta, state.val);
            if(state.beta <= state.alfa)
                break;
        }
    }

    make_step(state, best_child);
}

// void smart_choose(State &state) {
//     // jeśli jeszcze nie tworzyłem dzieci dla state
//     if (state.children.empty()) {
//         vector<pii> possible_moves = generate_moves(state);
//         for (const auto& move : possible_moves) {
//             State* child = new State;
//             make_child_from_state(state, *child, move);
//             ll hsh = make_hsh(*child);
//             if(hsh_set.count(hsh) == 0){
//                 state.children.push_back(child);
//                 hsh_set.insert(hsh);
//             }
//         }
//     }

//     // już miałem dzieci 
//     State* best_child = nullptr;
//     vector<std::thread> threads;

//     // Launch threads for min_max on each child
//     for (auto& child : state.children) {
//         child->deep = state.deep + 1;
//         child->alfa = state.alfa;
//         child->beta = state.beta;
//         child->val = (child->player == max_player ? -inf : inf);

//         // Using lambda to call min_max_threaded
//         threads.emplace_back([child]() {
//             min_max(*child);
//         });
//     }

//     // Wait for all threads to complete
//     for (auto& thread : threads) {
//         thread.join();
//     }

//     // Evaluate the best move based on updated child states
//     for (auto& child : state.children) {
//         if (state.player == max_player) {
//             if (child->val > state.val) {
//                 state.val = child->val;
//                 best_child = child;
//             }
//             state.alfa = std::max(state.alfa, state.val);
//             if (state.beta <= state.alfa) break;
//         } else if (state.player == min_player) {
//             if (child->val < state.val) {
//                 state.val = child->val;
//                 best_child = child;
//             }
//             state.beta = std::min(state.beta, state.val);
//             if (state.beta <= state.alfa) break;
//         }
//     }

//     make_step(state, best_child);
// }
