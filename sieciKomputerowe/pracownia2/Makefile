CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJECTS = main.o router.o socket.o utils.o
TARGET = router

.PHONY: clean distclean

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS)

distclean: clean
	rm -f $(TARGET)