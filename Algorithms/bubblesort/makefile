CC = g++
CFLAGS = -std=c++11 -Wall

all: bubblesort

bubblesort: bubblesort.cpp
	$(CC) $(CFLAGS) -o bubblesort bubblesort.cpp

run: bubblesort
	./bubblesort

clean:
	rm -f bubblesort

.PHONY: all run clean

