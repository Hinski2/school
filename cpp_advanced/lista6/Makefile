CXX ?= g++
CXXFLAGS ?= -std=c++23

SOURCES := $(wildcard *.cpp)
BINS    := $(SOURCES:%.cpp=%)

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(BINS)

.PHONY: all clean
