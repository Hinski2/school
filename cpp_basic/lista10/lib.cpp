#include "lib.hpp"

std::istream& clearline(std::istream& is) {
    for(char ch; is.get(ch) && ch != '\n';) {
    }
    return is;
}

ignore_param ignore(int x) {
    return {x};
}

std::istream& operator>>(std::istream& is, ignore_param param) {
    if(param.count > 0) {
        is.ignore(param.count, '\n');
    }
    return is;
}

std::ostream& comma(std::ostream& os) {
    os << ", ";
    return os;
}

std::ostream& colon(std::ostream& os) {
    os << ": ";
    return os;
}

index_param index(int x, int w) {
    return {x, w};
}

std::ostream& operator<<(std::ostream& os, index_param param) {
    os << '[' << std::setw(param.w) << std::right << param.x << ']' << std::left;
    return os;
}

// B

ifsbin::ifsbin(const std::string& path) {
    in.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    in.open(path, std::ios::binary);
}

ifsbin::~ifsbin() {
    if(in.is_open()) {
        try {
            in.exceptions(std::ios_base::goodbit);
            in.close();
        } catch(...) {
        }
    }
}

ifsbin& ifsbin::operator>>(std::string& value) {
    value.clear();
    for(char ch; ; ) {
        in.read(&ch, 1);
        if(ch == '\0') {
            break;
        }
        value.push_back(ch);
    }
    return *this;
}

ofsbin::ofsbin(const std::string& path) {
    out.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    out.open(path, std::ios::binary);
}

ofsbin::~ofsbin() {
    if(out.is_open()) {
        try {
            out.exceptions(std::ios_base::goodbit);
            out.close();
        } catch(...) {
        }
    }
}

ofsbin& ofsbin::operator<<(const std::string& value) {
    out.write(value.c_str(), value.size() + 1);
    return *this;
}
