all: test proc solve brute

test: arr.c
	gcc -O2 -g -o test arr.c

proc: proc.c
	gcc -O0 -g -o proc proc.c

solve: solve.c
	gcc -O0 -g -o solve solve.c

brute: brute.c
	gcc -O0 -g -o brute brute.c

clean:
	rm -f test proc solve brute