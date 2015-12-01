all: hello.out sorting_numbers.out

clean: 
	rm -f *.out

%.out: %.c
	gcc -std=gnu11 -o $@ $^

.PHONY:
	all clean
