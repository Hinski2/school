CXX ?= g++
CXXFLAGS ?= -std=c++23 -Wall

SOURCES := $(wildcard *.cpp) $(wildcard lexer/*.cpp) $(wildcard expr/*.cpp) $(wildcard parser/*.cpp)
LIBS := $(wildcard *.hpp) $(wildcard lexer/*.hpp) $(wildcard expr/*.hpp) $(wildcard parser/*.hpp)
OBJS := $(SOURCES:.cpp=.o)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

%.o: %.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) main

.PHONY: all clean
