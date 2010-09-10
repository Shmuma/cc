all: test gen

test: 725.cpp
	g++ -o test -O0 -g 725.cpp

gen: 725-gen.cpp
	g++ -o gen -O0 -g 725-gen.cpp

clean:
	-rm -f test