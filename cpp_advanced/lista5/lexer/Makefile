CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2

SRC := main.cpp token.cpp
OBJ := $(SRC:.cpp=.o)
BIN := lexer

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
