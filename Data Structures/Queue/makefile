CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

main.o: main.cpp myqueue.h
	$(CXX) $(CXXFLAGS) -c main.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)