all: test proc

test: arr.c
	gcc -O2 -g -o test arr.c

proc: proc.c
	gcc -O0 -g -o proc proc.c

clean:
	rm -f test proc