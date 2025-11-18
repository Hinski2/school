CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2 -I.

SRC := \
    main.cpp \
    lexer/token.cpp \
    parser/precedenceClimbingParser.cpp \
    parser/recursiveDescentParser.cpp \
    parser/utils.cpp

OBJ := $(SRC:.cpp=.o)

BIN := sigmapp

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean