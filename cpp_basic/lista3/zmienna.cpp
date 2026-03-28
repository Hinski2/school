#include "zmienna.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>

size_t Zmienna::top_idx() const {
    return (start_idx + no_items - 1) % MAX_HIST_LEN;
}
void Zmienna::push(double val) {
    if (no_items < MAX_HIST_LEN) {
        history[top_idx() + 1] = val;
        no_items++;
    } else {
        history[start_idx] = val;
        start_idx = (start_idx + 1) % MAX_HIST_LEN;
    }
}

// konstruktory
Zmienna::Zmienna(const std::string& name, double val) 
    : name(name), history(new double[MAX_HIST_LEN]), start_idx(0), no_items(1)
{
   history[0] = val; 
}
Zmienna::Zmienna() 
    : Zmienna("default", .0) 
{}
Zmienna::Zmienna(const Zmienna& other) 
    : Zmienna(other.name, other.history[other.top_idx()])
{}
Zmienna::Zmienna(Zmienna&& other) noexcept 
    : name(std::move(other.name)), history(other.history), start_idx(other.start_idx), no_items(other.no_items)
{
    other.history = nullptr;
    other.start_idx = other.no_items = 0;
}

// destruktor
Zmienna::~Zmienna() {
    delete[] history;
    start_idx = no_items = 0;
}

//
Zmienna& Zmienna::operator=(const Zmienna& other) {
    if (this != &other) {
        push(other.history[other.top_idx()]);
    }

    return *this;
}
Zmienna& Zmienna::operator=(Zmienna&& other) noexcept {
    if (this != &other) {
        push(other.history[other.top_idx()]);
    }

    return *this;
}

// utils
Zmienna& Zmienna::operator=(const double d) {
    push(d);
    return *this;
}
void Zmienna::undo() {
    if(no_items) no_items--;
}
void Zmienna::negate() {
    push(-history[top_idx()]);
}
void Zmienna::invert() {
    if(history[top_idx()] == .0) throw std::runtime_error("0 division");
    push(1. / history[top_idx()]);
}
double Zmienna::get_val() const {
    return history[top_idx()];
}
const std::string& Zmienna::get_name() const {
    return name;
}

std::ostream& operator<<(std::ostream& out, const Zmienna& z) {
    out << z.get_name() << std::endl;
    for(size_t i = 0; i < z.no_items; i++)
        out << z.history[(i + z.start_idx) % z.MAX_HIST_LEN] << std::endl;

    return out;
}
