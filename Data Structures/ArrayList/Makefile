CC = g++
CFLAGS = -std=c++11 -Wall

all: main

bubblesort: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

run: main
	./main

clean:
	rm -f main

.PHONY: all run clean
