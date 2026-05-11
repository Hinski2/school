CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

OBJS = transport.o socket/udpSocket.o utils/chunk.o utils/receiver.o utils/transportMessage.o
TARGET = transport

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

distclean: clean
	rm -f $(TARGET)

clean:
	rm -f $(OBJS)

.PHONY: all clean distclean
