CXX ?= g++
CXXFLAGS ?= -std=c++23 -Wall

SOURCES := $(wildcard *.cpp)
LIBS := $(wildcard *.hpp)
OBJS := $(SOURCES:.cpp=.o)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

%.o: %.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BINS)

.PHONY: all clean
