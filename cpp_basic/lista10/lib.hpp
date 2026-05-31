#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

std::istream& clearline(std::istream& is);

struct ignore_param {
    int count;
};

ignore_param ignore(int x);
std::istream& operator>>(std::istream& is, ignore_param param);

std::ostream& comma(std::ostream& os);
std::ostream& colon(std::ostream& os);

struct index_param {
    int x;
    int w;
};

index_param index(int x, int w);
std::ostream& operator<<(std::ostream& os, index_param param);


// B

class ifsbin {
public:
    explicit ifsbin(const std::string& path);
    ~ifsbin();

    template<typename T>
    ifsbin& operator>>(T& value) {
        in.read(reinterpret_cast<char*>(&value), sizeof(T));
        return *this;
    }

    ifsbin& operator>>(std::string& value);

private:
    std::ifstream in;
};

class ofsbin {
public:
    explicit ofsbin(const std::string& path);
    ~ofsbin();

    template<typename T>
    ofsbin& operator<<(const T& value) {
        out.write(reinterpret_cast<const char*>(&value), sizeof(T));
        return *this;
    }

    ofsbin& operator<<(const std::string& value);

private:
    std::ofstream out;
};
