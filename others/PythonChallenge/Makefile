all: 2.run 3.run

%.run: %.c
	gcc -o $@ -g -O0 $^

clean:
	rm -f *.run