CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = ONP
SRC = ONP.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

main.o: ONP.cpp stack.h
	$(CXX) $(CXXFLAGS) -c ONP.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)