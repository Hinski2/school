CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

OBJS = traceroute.o icmp/icmp_socket.o icmp/icmp_send.o icmp/icmp_recv.o utils/utils.o
TARGET = traceroute

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
