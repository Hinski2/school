#include <bits/stdc++.h>
using namespace std;

//enumy
enum animal_enum {NO_ANIMAL, RAT, CAT, DOG, WOLF, JAGUAR, TIGER, LION, ELEPHANT};
enum type_enum {FIELD, TRAP, RIVER, DEN_P1, DEN_P2};
enum player_enum {P1, P2, NO_PLAYER};

//skróty
#define fi first
#define se second

//typy danych
typedef pair<short, short> pss;

//consty
const int inf = 1e9 + 7;
const short n = 9, m = 7;
const short tile_type[n][m] = {
    {FIELD, FIELD, TRAP, DEN_P1, TRAP, FIELD, FIELD},
    {FIELD, FIELD, FIELD, TRAP, FIELD, FIELD, FIELD},
    {FIELD, FIELD, FIELD, FIELD, FIELD, FIELD, FIELD},
    {FIELD, RIVER, RIVER, FIELD, RIVER, RIVER, FIELD},
    {FIELD, RIVER, RIVER, FIELD, RIVER, RIVER, FIELD},
    {FIELD, RIVER, RIVER, FIELD, RIVER, RIVER, FIELD},
    {FIELD, FIELD, FIELD, FIELD, FIELD, FIELD, FIELD},
    {FIELD, FIELD, FIELD, TRAP, FIELD, FIELD, FIELD},
    {FIELD, FIELD, TRAP, DEN_P2, TRAP, FIELD, FIELD}};
const pss shift[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

//struktury
struct pon {
    animal_enum animal;
    player_enum player;
};

struct move_struct {
    pss from;
    pss shift;
};

//funcje pomocjicze
inline bool valid_coord(pss p);

//generowanie ziarna
long seed() {
    auto t=chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
}

//klasa przedstawiająca stan gry
class State {
public:
    short player;                       // który gracz wykonuje ruch
    vector<vector<pon>> board;          // nasza plansza
    vector<vector<pss>> animal_poss;    // dokładne pozycje zwierząt

    //konstruktor
    State(short player, vector<vector<pon>> board, vector<vector<pss>> animal_poss) : player(player), board(board), animal_poss(animal_poss) {}

    //destruktor
    ~State() {
    }

    // wypisanie planszy
    void print() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                char c;
                if(board[i][j].animal == NO_ANIMAL) c = '.';
                else if(board[i][j].animal == RAT) c = 'R' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == CAT) c = 'C' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == DOG) c = 'D' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == WOLF) c = 'W' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == JAGUAR) c = 'J' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == TIGER) c = 'T' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == LION) c = 'L' | ((board[i][j].player == P1) * 32);
                else if(board[i][j].animal == ELEPHANT) c = 'E' | ((board[i][j].player == P1) * 32);

                cout << c;
            }
            cout << endl;
        }
        cout << endl;
    }

    vector<move_struct> generate_possible_moves() {
        vector<move_struct> possible_moves;
        pss my_den = (player == P1 ? make_pair(0, 3) : make_pair(8, 3));
        for(int animal = 1; animal < 9; animal++) {
            if(animal_poss[player][animal] == (pss) {-1, -1}) continue; //jeśli to zwierze jest zbite

            for(auto s: shift){
                pss poss = {animal_poss[player][animal].fi + s.fi, animal_poss[player][animal].se + s.se};

                //początkowe / ogólne sprawdzenia
                if(!valid_coord(poss)) continue; //jeśli wychodzimy poza plansza
                if(board[poss.fi][poss.se].animal != NO_ANIMAL && board[poss.fi][poss.se].player == player) continue; // jeśli w poss znajduje się zwierze i to nasze zwierze
                if(poss == my_den) continue; //jeśli whodzimy do swojej jamy
                if(animal != RAT && animal != TIGER && animal != LION && tile_type[poss.fi][poss.se] == RIVER) continue; // tylko szczur może wchodzić do wody,a tygrys i lew mogą nad nią skakać

                switch(animal) {
                    case RAT:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > RAT && board[poss.fi][poss.se].animal != ELEPHANT) continue;
                        if(tile_type[animal_poss[player][animal].fi][animal_poss[player][animal].se] == RIVER && tile_type[poss.fi][poss.se] != RIVER && board[poss.fi][poss.se].animal) continue; //jeśli szczur był w wodzi i z niej wychodzi to nie może bić
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case CAT:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > CAT) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case DOG:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > DOG) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case WOLF:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > WOLF) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case JAGUAR:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > JAGUAR) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case TIGER:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > TIGER) continue;
                        if(tile_type[poss.fi][poss.se] == RIVER) poss = make_jump_over_water(poss, animal, s);
                        if(poss == (pss){-1, -1}) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case LION:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > LION) continue;
                        if(tile_type[poss.fi][poss.se] == RIVER) poss = make_jump_over_water(poss, animal, s);
                        if(poss == (pss){-1, -1}) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;

                    case ELEPHANT:
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal > ELEPHANT) continue;
                        possible_moves.push_back({animal_poss[player][animal], s});
                        break;                        
                }
            }
        }

        return possible_moves;
    }

    inline pss make_jump_over_water(pss poss, int animal, pss s) {
        while(tile_type[poss.fi][poss.se] == RIVER){
            if(board[poss.fi][poss.se].animal > 0){ //trafiliśmy na szczura
                poss = {-1, -1};
                return poss;
            }

            poss.fi += s.fi, poss.se += s.se; //lecimy dalej jak Jordan
        }

        if(board[poss.fi][poss.se].player == player || board[poss.fi][poss.se].animal > animal) poss = {-1, -1}; //przeskoczyliśmy wode ale wskakujemy na nasze inne zwierze albo na zwirze przeciwnika o większej mocy
        return poss;
    }

    void do_move(move_struct move){
        short animal = board[move.from.fi][move.from.se].animal;
        pss new_poss = {move.from.fi + move.shift.fi, move.from.se + move.shift.se};

        if(board[new_poss.fi][new_poss.se].animal) //zbijam zwierze przeciwnikowi
            animal_poss[player ^ 1][board[new_poss.fi][new_poss.se].animal] = {-1, -1};

        board[move.from.fi][move.from.se] = {NO_ANIMAL, NO_PLAYER};                         // czyszcze stare pole
        board[new_poss.fi][new_poss.se] = {(animal_enum) animal, (player_enum) player};     // ustawiam nowe pole
        animal_poss[player][animal] = new_poss;                                             // zmieniam pozycje mojego zwierzaka w spisie pozycji zwierząt
    }

    inline int no_of_animals(short p){
        int ans = 0;
        for(int i = 1; i < 9; i++)
            if(animal_poss[p][i] != (pss) {-1, -1}) ans++;
        return ans;
    }

    int cnt_aval_pons(short p){
        int cnt = 0;
        for(int i = 1; i < 9; i++)
            if(animal_poss[p][i] != (pss) {-1, -1}) cnt++;
        return cnt;
    }

    int evaluate(int noumber_of_games) {
        player ^= 1;
        int ans = 0;
        for(int i = 0; i < noumber_of_games; i++) {
            // robimy kopie
            short copy_of_player = player;
            vector<vector<pon>> copy_of_board = board;
            vector<vector<pss>> copy_of_animal_poss = animal_poss;

            int cnt = 100;
            int no_pons_p1 = cnt_aval_pons(P1), no_pons_p2 = cnt_aval_pons(P2); // liczba pionków przed robieniem ruchów
            while(!game_over()) {
                if(!cnt) break;
                // generujemy wszystkie ruchy
                vector<move_struct> possible_moves = generate_possible_moves();

                //wybieramy losowy
                move_struct chosen_move = possible_moves[rand() % possible_moves.size()];

                // robimy ten ruch
                do_move(chosen_move);

                // zminiamy state (pozostała tylko zmiana gracza)
                player ^= 1;
                cnt--;
            }

            //doszliśmy do końca gry
            ans += heura(cnt, no_pons_p1, no_pons_p2);
            player = copy_of_player ^ 1;
            board = copy_of_board; // przywracanie sptanu z przed ewaluacji
            animal_poss = copy_of_animal_poss;
        }

        return ans;
    }

    int dist_from_edge(){
        int ans = 0;
        if(player == P1){
            for(int i = 1; i < 9; i++)
                if(animal_poss[player][i] != (pss) {-1, -1})
                    ans += animal_poss[player][i].fi;
        }
        else{
            for(int i = 1; i < 9; i++)
                if(animal_poss[player][i] != (pss) {-1, -1})
                    ans += 8 - animal_poss[player][i].fi;
        }

        return ans;
    }

    int heura(int cnt, int pons_before_p1, int pons_before_p2){
        int ans = 0, pons_after_p1 = cnt_aval_pons(P1), pons_after_p2 = cnt_aval_pons(P2);
        // ans += dist_from_edge() * (cnt / 10 + 1); 

        if(player == P1){
            ans += 10 * (pons_after_p1 - pons_before_p1);
            ans -= 10 * (pons_after_p2 - pons_before_p2);
        }
        else{
            ans -= 10 * (pons_after_p1 - pons_before_p1);
            ans += 10 * (pons_after_p2 - pons_before_p2);
        }

        ans += 1000 * dist_from_edge() * (cnt / 10 + 1);
        return ans;
    }

    inline bool game_over() {
        if(board[0][3].animal || board[8][3].animal) return 1;
        return generate_possible_moves().size() == 0;
    } 
};

void make_random_move(State &s) {
    vector<move_struct> possible_moves = s.generate_possible_moves();
    int choosen_move = rand() % possible_moves.size();

    s.do_move(possible_moves[choosen_move]);
    s.player ^= 1;
}

void make_smart_move(State &s) {
    vector<move_struct> possible_moves = s.generate_possible_moves();   // generacja wszystkich ruchów 
    pair<move_struct, int> best_move; best_move.se = -inf;              // najlepszy ruch

    int no_sym = 750 / possible_moves.size();                           // liczba symulacji dla każdego mov
    for(auto move: possible_moves){
        State next_s(s.player, s.board, s.animal_poss);
        next_s.do_move(move);
        int eval = next_s.evaluate(no_sym); 
        if(eval > best_move.se){
            best_move.se = eval;
            best_move.fi = move;
        }
    }
    s.do_move(best_move.fi);
    s.player ^= 1;
}

int main(){
    //ustawianie gry
    srand(seed());
    pss score = {0, 0};
    for(int i = 0; i < 1000; i++){
        vector<vector<pon>> init_board(n, vector<pon>(m, {NO_ANIMAL, NO_PLAYER}));
        short player = P1;
        init_board[0][0] = {LION, P1}, init_board[0][6] = {TIGER, P1}, init_board[1][1] = {DOG, P1}, init_board[1][5] = {CAT, P1}, init_board[2][0] = {RAT, P1}, init_board[2][2] = {JAGUAR, P1}, init_board[2][4] = {WOLF, P1}, init_board[2][6] = {ELEPHANT, P1};
        init_board[8][6] = {LION, P2}, init_board[8][0] = {TIGER, P2}, init_board[7][5] = {DOG, P2}, init_board[7][1] = {CAT, P2}, init_board[6][6] = {RAT, P2}, init_board[6][4] = {JAGUAR, P2}, init_board[6][2] = {WOLF, P2}, init_board[6][0] = {ELEPHANT, P2};

        vector<vector<pss>> animal_poss(2, vector<pss>(9));
        animal_poss[P1][LION] = {0, 0}, animal_poss[P1][TIGER] = {0, 6}, animal_poss[P1][DOG] = {1, 1}, animal_poss[P1][CAT] = {1, 5}, animal_poss[P1][RAT] = {2, 0}, animal_poss[P1][JAGUAR] = {2, 2}, animal_poss[P1][WOLF] = {2, 4}, animal_poss[P1][ELEPHANT] = {2, 6};
        animal_poss[P2][LION] = {8, 6}, animal_poss[P2][TIGER] = {8, 0}, animal_poss[P2][DOG] = {7, 5}, animal_poss[P2][CAT] = {7, 1}, animal_poss[P2][RAT] = {6, 6}, animal_poss[P2][JAGUAR] = {6, 4}, animal_poss[P2][WOLF] = {6, 2}, animal_poss[P2][ELEPHANT] = {6, 0};

        State s(player, init_board, animal_poss);

        //graj dopuki ktoś nie wygrał
        int move_type = 1;
        while(!s.game_over()){
            if(move_type == 0)
                make_smart_move(s);
            else
                make_random_move(s);
            
            move_type ^= 1;
            s.print();
        }


        //zmiana wyniku
        if(s.board[0][3].animal) score.se++;
        else score.fi++;

        //wypisanie wyniku
        cout << score.fi << ' ' << score.se << endl;
    }

}

inline bool valid_coord(pss p){
    return 0 <= p.fi && p.fi < n && 0 <= p.se && p.se < m;
}