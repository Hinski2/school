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
typedef long long ll;

//consty
const long long inf = 1e12 + 7;
const double dinf = 1e4 + 7;
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

// dane do min_maxa
short max_player, min_player;
const short max_deep = 5;

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
                        if(tile_type[poss.fi][poss.se] != TRAP && (board[poss.fi][poss.se].animal > RAT && board[poss.fi][poss.se].animal != ELEPHANT)) continue;
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
                        if(tile_type[poss.fi][poss.se] != TRAP && board[poss.fi][poss.se].animal == RAT) continue;
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

    inline int cnt_aval_pons(short p){
        int cnt = 0;
        for(int i = 1; i < 9; i++)
            if(animal_poss[p][i] != (pss) {-1, -1}) cnt += i;
        return cnt;
    }

    ll evaluate(int noumber_of_games) {
        ll ans = 0;
        for(int i = 0; i < noumber_of_games; i++) {
            // robimy kop2e
            short copy_of_player = player;
            vector<vector<pon>> copy_of_board = board;
            vector<vector<pss>> copy_of_animal_poss = animal_poss;

            int cnt = 15;
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

            player = copy_of_player;
            ans += heura(cnt, no_pons_p1, no_pons_p2);
            board = copy_of_board; // przywracanie sptanu z przed ewaluacji
            animal_poss = copy_of_animal_poss;
        }

        return ans;
    }

    int dist_from_edge(int p){
        int ans = 0;
        if(p == P1){
            for(int i = 1; i < 9; i++)
                if(animal_poss[p][i] != (pss) {-1, -1})
                    ans += animal_poss[p][i].fi;
        }
        else{
            for(int i = 1; i < 9; i++)
                if(animal_poss[p][i] != (pss) {-1, -1})
                    ans += 8 - animal_poss[p][i].fi;
        }

        return ans;
    }

    int dist_from_opponent_base(int p){ //im blirzej jego bazy tym większy wynik
        int ans = 0;

        if(p == P1){
            for(int i = 1; i < 9; i++)
                if(animal_poss[p][i] != (pss) {-1, -1})
                    ans += i * (11 - (abs(8 - animal_poss[p][i].fi) + abs(3 - animal_poss[p][i].se)));
        }
        else{
            for(int i = 1; i < 9; i++)
                if(animal_poss[p][i] != (pss) {-1, -1})
                    ans += i * (11 - (abs(0 - animal_poss[p][i].fi) + abs(3 - animal_poss[p][i].se)));
        }

        return ans;
    }

    ll heura(int cnt, int pons_before_p1, int pons_before_p2){
        ll ans = 0, pons_after_p1 = cnt_aval_pons(P1), pons_after_p2 = cnt_aval_pons(P2);

        if(player == P1){
            ans += 2 * (pons_after_p1 - pons_before_p1);
            ans -= 2 * (pons_after_p2 - pons_before_p2);

            if(board[8][3].animal) ans = inf;
            else if(board[0][3].animal) ans = -inf;
        }
        else{
            ans -= 2 * (pons_after_p1 - pons_before_p1);
            ans += 2 * (pons_after_p2 - pons_before_p2);

            if(board[8][3].animal) ans = -inf;
            else if(board[0][3].animal) ans = inf;
        }

        int dist = dist_from_opponent_base(player);
        ans += 10 * dist * dist * (cnt + 1);
        return ans;
    }

    inline bool game_over() {
        if(board[0][3].animal || board[8][3].animal) return 1;
        return generate_possible_moves().size() == 0;
    } 
};

class Alfa_beta_state : public State {
public:
    ll deep, alfa, beta, val;
    Alfa_beta_state *root;

    //implementacja
    ll heura(){
        int pons_before_p1 = root -> cnt_aval_pons(P1), pons_before_p2 = root -> cnt_aval_pons(P2);
        int pons_after_p1 = cnt_aval_pons(P1), pons_after_p2 = cnt_aval_pons(P2);
        if(max_deep % 2 == 0) player ^= 1;
        ll ans = 0;

        if(player == P1){
            ans -= 20 * (pons_before_p1 - pons_after_p1); //odejmuje zmiane w moich
            ans += 20 * (pons_before_p2 - pons_after_p2); //dodaje zmiane w jego

            if(board[8][3].animal) ans = -inf;
            else if(board[0][3].animal) ans = inf;
        }
        else{
            ans += 20 * (pons_before_p1 - pons_after_p1);
            ans -= 20 * (pons_before_p2 - pons_after_p2);

            if(board[8][3].animal) ans = -inf;
            else if(board[0][3].animal) ans = inf;
        }
        ans *= max_deep - deep + 1;
        if(ans == inf || ans == -inf)
        {
            if(max_deep % 2 == 0) player ^= 1;
            return ans;
        }

        ans += dist_from_opponent_base(player) * dist_from_opponent_base(player) - dist_from_opponent_base(player^1) * dist_from_opponent_base(player^1);
        if(max_deep % 2 == 0) player ^= 1;
        return ans;
    }

    void alfa_beta(){
        // jeśli doszedłem do końca
        if(deep == max_deep || game_over()){
            val = heura();
        }

        // to jeszcze nie jest koniec lecimy dalej
        else{
            // teraz moge deopiero zmienić gracza
            player ^= 1;

            // najpierw ustawiamy val
            if(player == max_player) val = -inf;
            else val = inf;

            vector<move_struct> possible_moves = generate_possible_moves();
            for(auto move: possible_moves){
                // tworzemy syna
                Alfa_beta_state son = Alfa_beta_state(player, board, animal_poss, alfa, beta, deep + 1, root);
                son.do_move(move);
                son.alfa_beta();

                //sprawdzamy czy dalej się opłaca przeszukiwać
                if(player == max_player){
                    val = max(val, son.val);
                    if(val > beta) break;
                    alfa = max(alfa, val);
                }
                else{
                    val = min(val, son.val);
                    if(val < alfa) break;
                    beta = min(beta, val);
                }
            }
        }
    }

    Alfa_beta_state(short player, vector<vector<pon>> board, vector<vector<pss>> animal_poss, double alfa, double beta, int deep, Alfa_beta_state *root) :
        State(player, board, animal_poss), alfa(alfa), beta(beta), deep(deep), root(root) {}
    ~Alfa_beta_state() {} //TODO
};

class Mcts_state : public State {
public:
    ll wins = 0;                    // liczba wygranych
    ll visited = 0;                 // liczba granych gier 
    vector<Mcts_state*> sons;       // wektor wskaźników na synów
    Mcts_state *parent;             // wsjaźnik na ojca
    move_struct obtained_by_move;   // żeby potem wiedzieć gdzie iść z roota

    // dostaje to samo co State + wskaźnik na rodzica (dla roota NULL)
    Mcts_state(short player, vector<vector<pon>> board, vector<vector<pss>> animal_poss, Mcts_state *parent, move_struct move = {{-1, -1}, {-1, -1}}) :
        State(player, board, animal_poss), parent(parent), obtained_by_move(move){}
    ~Mcts_state(){
        for(auto son: sons)
            delete son;
    }

    inline double normalize(double score, double mini, double maxi){
        return (score - mini) / (maxi - mini);
    }

    ll heura(int cnt, int pons_before_maxp, int pons_before_minp){
        int pons_after_maxp = cnt_aval_pons(max_player), pons_after_minp = cnt_aval_pons(min_player);
        ll ans = 0;

        ans -= 20 * (pons_before_maxp - pons_after_maxp);
        ans += 20 * (pons_before_minp - pons_after_minp);
        if(max_player == P1){
            if(board[0][3].animal) ans = -inf;
            else if(board[8][3].animal) ans = inf;
        }
        else{
            if(board[0][3].animal) ans = inf;
            else if(board[8][3].animal) ans = -inf;
        }

        ans *= cnt + 1;
        if(ans == inf || ans == -inf)
        {
            return ans;
        }

        ans += dist_from_opponent_base(max_player) * dist_from_opponent_base(max_player) - dist_from_opponent_base(min_player) * dist_from_opponent_base(min_player);
        return ans;
    }


    //implementacja
    void backpropagate(ll score){
        visited++;
        wins += score;
        if(parent != NULL)
            parent -> backpropagate(score);
    }

    void make_sons(){
        vector<move_struct> possible_moves = generate_possible_moves();
        sons.resize(possible_moves.size());

        int i = 0;
        for(auto move: possible_moves){
            Mcts_state *son = new Mcts_state(player, board, animal_poss, this, move);
            son -> do_move(move);
            son -> player = player;
            sons[i++] = son; 
        }
    }

    Mcts_state *select(){
        Mcts_state *best = this;
        double value_of_best = -dinf;
        if(sons.empty()) return this; //doszedłem do liścia

        for(auto son: sons){
            double val = son -> uct();
            if(val > value_of_best){
                value_of_best = val;
                best = son;
            }
        }

        return best -> select();
    }

    inline double uct(){
        if(visited == 0) return dinf;
        return (double) wins / visited + sqrt(2) * sqrt(log(parent == NULL ? visited : parent -> visited) / visited);
    }

    void symulate(){ //robi symulacje do końca, robie to dla liści 
        // robie kopie
        short copy_of_player = player;
        vector<vector<pon>> copy_of_board = board;
        vector<vector<pss>> copy_of_animal_poss = animal_poss;

        int cnt = 9;
        int no_pons_maxp, no_pons_minp;
        if(parent != NULL){
            no_pons_maxp = parent -> cnt_aval_pons(max_player);
            no_pons_minp = parent -> cnt_aval_pons(min_player);
        }
        else{
            no_pons_maxp = cnt_aval_pons(max_player);
            no_pons_minp = cnt_aval_pons(min_player);
        }

        while(!game_over()) {
            if(!cnt) break;
            // generujemy wszystkie ruchy
            vector<move_struct> possible_moves = generate_possible_moves();

            // wybieramy losowy
            move_struct chosen_move = possible_moves[rand() % possible_moves.size()];

            // robimy ten ruch
            do_move(chosen_move);

            // zmieniamy sate
            player ^= 1;
            cnt--;
        }

        // doszliśmy do końca gry
        player = copy_of_player;
        ll score = heura(cnt, no_pons_maxp, no_pons_minp), ans;
        if(score == inf) ans = 2 * (sqrt(cnt) + 1);
        else if(score == -inf) ans = -2 *(sqrt(cnt) + 1);
        else ans = (score > 0);
        backpropagate(ans);
        board = copy_of_board;
        animal_poss = copy_of_animal_poss;
    }

};

void make_move_bot3(State &s) { // bot alfa beta
    max_player = s.player;
    min_player = s.player^1;

    // tworzenie wierzchołka
    Alfa_beta_state root = Alfa_beta_state(s.player, s.board, s.animal_poss, -inf, inf, 0, NULL);

    vector<pair<move_struct, ll>> best_moves(1); // jaki to ruch jest najlepszy oraz jego val3
    best_moves[0].se = -inf;

    //robie symulacje dla
    vector<move_struct> possible_moves = root.generate_possible_moves();
    for(auto move: possible_moves){
        // tworzenie syna
        Alfa_beta_state son = Alfa_beta_state(s.player, s.board, s.animal_poss, root.alfa, root.beta, 1, &root);
        son.do_move(move);

        //syn jest gotowy można robić na nim alfa bete
        son.alfa_beta(); 

        // sprawdzam czy ten syn jest najlepszym wyborem
        if(son.val > best_moves[0].se){
            best_moves.resize(1);
            best_moves[0] = {move, son.val};
        }
    }

    // już mam wybrany najlepszy ruch, czas zmienić state
    move_struct move = best_moves[rand() % best_moves.size()].fi;
    s.do_move(move);
    s.player ^= 1;
}

void make_move_bot2(State &s) { //bot mcts
    max_player = s.player;
    min_player = s.player^1;
    Mcts_state *root = new Mcts_state(s.player, s.board, s.animal_poss, NULL);
    Mcts_state *best = NULL;
    ll value_of_best = -inf;
    pss my_den = (s.player == P1 ? make_pair(0, 3) : make_pair(8, 3));

    for(int i = 0; i < 15000; i++){
        // wybieramy liścia którego będziemy rozwijac
        Mcts_state *leaf = root -> select();

        //tworzymy synów dla wierzchołka
        leaf -> make_sons();

        //przyśpieszenie
        if(leaf -> game_over() && leaf -> parent == root){
            if(leaf -> board[my_den.fi][my_den.se].animal) leaf -> visited = -inf;
            else leaf -> wins = inf;
        }

        //jeśli liściowi nie wygenerowali się synowie -> to robie symulacje dla tego leaf
        if(leaf -> sons.empty()){   
            leaf -> symulate();
        }
        //liściowi wygenerowali się synowie
        else{
            leaf -> sons.front() -> symulate(); //wybieram pierwszego lepszego skoro i tak żaden z nich nie został odwiedzony
            leaf -> sons.front() -> player ^= 1;
        }
    }

    // wynieram gdzie isć
    for(auto son: root -> sons){
        ll val = son -> visited;
        if(val > value_of_best || best == NULL){
            value_of_best = val;
            best = son;
        }
    }

    s.do_move(best -> obtained_by_move);
    s.player ^= 1;
    delete root;
}

void make_move_bot1(State &s) { //bot zad3
    vector<move_struct> possible_moves = s.generate_possible_moves();   // generacja wszystkich ruchów 
    pair<move_struct, ll> best_move; best_move.se = -inf;              // najlepszy ruch

    int no_sym = 1000 / possible_moves.size();                           // liczba symulacji dla każdego mov
    for(auto move: possible_moves){
        State next_s(s.player, s.board, s.animal_poss);
        next_s.do_move(move);
        ll eval = next_s.evaluate(no_sym); 
        if(eval > best_move.se){
            best_move.se = eval;
            best_move.fi = move;
        }
    }
    s.do_move(best_move.fi);
    s.player ^= 1;
}

void make_move_bot0(State &s) { // całkowicie randomowy bot
    vector<move_struct> possible_moves = s.generate_possible_moves();
    int choosen = random() % possible_moves.size();
    s.do_move(possible_moves[choosen]);
    s.player ^= 1;
}



int main(){
    //ustawianie gry
    pss score = {0, 0};
    for(int i = 0; i < 10; i++){
        srand(seed());
        vector<vector<pon>> init_board(n, vector<pon>(m, {NO_ANIMAL, NO_PLAYER}));
        short player = (i < 5 ? P1 : P2); //!!! kto zaczyna
        init_board[0][0] = {LION, P1}, init_board[0][6] = {TIGER, P1}, init_board[1][1] = {DOG, P1}, init_board[1][5] = {CAT, P1}, init_board[2][0] = {RAT, P1}, init_board[2][2] = {JAGUAR, P1}, init_board[2][4] = {WOLF, P1}, init_board[2][6] = {ELEPHANT, P1};
        init_board[8][6] = {LION, P2}, init_board[8][0] = {TIGER, P2}, init_board[7][5] = {DOG, P2}, init_board[7][1] = {CAT, P2}, init_board[6][6] = {RAT, P2}, init_board[6][4] = {JAGUAR, P2}, init_board[6][2] = {WOLF, P2}, init_board[6][0] = {ELEPHANT, P2};

        vector<vector<pss>> animal_poss(2, vector<pss>(9));
        animal_poss[P1][LION] = {0, 0}, animal_poss[P1][TIGER] = {0, 6}, animal_poss[P1][DOG] = {1, 1}, animal_poss[P1][CAT] = {1, 5}, animal_poss[P1][RAT] = {2, 0}, animal_poss[P1][JAGUAR] = {2, 2}, animal_poss[P1][WOLF] = {2, 4}, animal_poss[P1][ELEPHANT] = {2, 6};
        animal_poss[P2][LION] = {8, 6}, animal_poss[P2][TIGER] = {8, 0}, animal_poss[P2][DOG] = {7, 5}, animal_poss[P2][CAT] = {7, 1}, animal_poss[P2][RAT] = {6, 6}, animal_poss[P2][JAGUAR] = {6, 4}, animal_poss[P2][WOLF] = {6, 2}, animal_poss[P2][ELEPHANT] = {6, 0};

        State s(player, init_board, animal_poss);

        int move_type = player;
        // bot0 - random
        // bot1 - zad3
        // bot2 - mcts
        // bot3 - alfa - beta
        while(!s.game_over()){              
            if(move_type == P1)     //P1 - góra   
                make_move_bot2(s);   
            else                    //P2 - dół
                make_move_bot3(s); 
            
            move_type ^= 1;
            s.print();
            cout << score.fi << ' ' << score.se << endl;
        }

        //sprawdzenie czy p2 ma wolne pionki
        int pons_p1 = 0;
        for(int i = 1; i < 9; i++)
            if(animal_poss[P1][i] != (pss) {-1, -1}) pons_p1++;


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