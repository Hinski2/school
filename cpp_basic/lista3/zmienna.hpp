#include <string>

class Zmienna {
    static constexpr size_t MAX_HIST_LEN = 3;

    const std::string name;
    double *history;
    size_t start_idx, no_items;
  
    size_t top_idx() const;
    void push(double val);
public:
    // konstruktory
    Zmienna(const std::string& name, double val);
    Zmienna();
    Zmienna(const Zmienna& other);
    Zmienna(Zmienna&& other) noexcept;

    // destruktory
    ~Zmienna();

    // 
    Zmienna& operator=(const Zmienna& other);
    Zmienna& operator=(Zmienna&& other) noexcept;

    // utls
    Zmienna& operator=(const double d);
    void undo();
    void negate();
    void invert();
    double get_val() const;
    const std::string& get_name() const;

    friend std::ostream& operator<<(std::ostream& out, const Zmienna& z);
};
