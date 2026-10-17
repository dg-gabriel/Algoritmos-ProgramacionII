CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++98
TARGET = arboles

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

main.o: main.cpp ArbolBin.hpp NodoBin.hpp ArbolN.hpp NodoN.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)