all: test test2

test: trip.c
	gcc -o test -g -O0 trip.c

test2: trip.cpp
	g++ -o test2 -g -O0 trip.cpp

clean:
	rm -f test test2