CC = g++
CFLAGS = -std=c++11 -Wall

all: mergesort

mergesort: mergesort.cpp
	$(CC) $(CFLAGS) -o mergesort mergesort.cpp

run: mergesort
	./mergesort

clean:
	rm -f mergesort

.PHONY: all run clean
