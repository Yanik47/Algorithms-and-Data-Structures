CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
TARGET = main
SRC = main.cpp

.PHONY all clean run

all: $(TARGET)
$(TARGET):$(SRC)
	$(SXX) $(SXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TAGET)