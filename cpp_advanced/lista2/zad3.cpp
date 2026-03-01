#include<bits/stdc++.h>
using namespace std;

enum class Sex {male, female};

class Lama {
public:
    string name;
    Sex sex;
    shared_ptr<Lama> mom, dad; 
    vector<weak_ptr<Lama>> kids;

    Lama(string name, Sex sex, vector<weak_ptr<Lama>> kids, shared_ptr<Lama> mom = nullptr, shared_ptr<Lama> dad = nullptr)
        : name(name), sex(sex), mom(mom), dad(dad), kids(kids) {
        }

    ~Lama() {
            cout << "delete:";
            cout << endl;
    }

    friend bool operator < (const Lama& a, const Lama &b) noexcept {
        size_t a_s = a.kids.size(), b_s = b.kids.size();
        return tie(a.name, a_s) < tie(b.name, b_s);
    }

    friend ostream& operator << (ostream& out, Lama lama) {
        out << "{" << endl;
        out << "    name: " << lama.name << endl;
        out << "    sex: " << (lama.sex == Sex::male ? "male" : "female") << endl;
        if(lama.mom)
        out << "    mom: " << lama.mom.get() -> name << endl; 
        if(lama.dad)
        out << "    dad: " << lama.dad.get() -> name << endl;
        out << "    kids: ";
        for(auto k: lama.kids)
            if(!k.expired()) cout << k.lock() -> name << ' ';
        out << endl;
        out << "}" << endl;

        return out;
    }
};

class Heard {
public:
    set<shared_ptr<Lama>> sl;

    friend ostream& operator << (ostream& out, Heard &h) {
        for(auto lama: h.sl)
            out << *lama << endl;
        out << endl;
        return out;
    }

    void buy(shared_ptr<Lama> lama) {
        sl.insert(lama);
    }

    void breed(shared_ptr<Lama> mom, shared_ptr<Lama> dad, shared_ptr<Lama> kid) {
        mom.get() -> kids.push_back(kid);
        dad.get() -> kids.push_back(kid);

        this -> sl.insert(kid);
    }

    void sell(string name) {
        auto it = find_if(sl.begin(), sl.end(), [&](auto& lama){ return lama -> name == name; });
        if (it != sl.end()) sl.erase(it);
    }
};

int main() {
    Heard heard;

    auto lena = make_shared<Lama>("Lena", Sex::female, vector<weak_ptr<Lama>>{});
    auto leo  = make_shared<Lama>("Leo",  Sex::male,   vector<weak_ptr<Lama>>{});

    heard.buy(lena);
    heard.buy(leo);
    cout << "po pierwszym zakupie" << endl;
    cout << heard << endl;

    cout << "tworzenie mowej lamy" << endl;
    heard.breed(lena, leo, make_shared<Lama>("matylda", Sex::female, vector<weak_ptr<Lama>>()));
    cout << heard << endl;

    heard.sell("matylda");
    cout << "po sprzedaży" << endl;
    cout << heard << endl;
}