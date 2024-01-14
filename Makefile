CC := gcc
CFLAGS := -W -Wall -pedantic -std=c99 -lm -fsanitize=address -g -ggdb 

test: test.c mlc.o arena.o linalg.o
	$(CC) $(CFLAGS) -o $@ $^

mlc.o: mlc.c 
	$(CC) $(CFLAGS) -c -o $@ $^

linalg.o: linalg.c 
	$(CC) $(CFLAGS) -c -o $@ $^

arena.o: arena.c
	$(CC) $(CFLAGS) -c -o $@ $^


clean:
	rm -f test
	rm -f *.o

.PHONY: clean
