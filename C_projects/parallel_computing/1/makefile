
CC=gcc

psrs: main.c main.h
	$(CC) $< -o $@.out -fopenmp -lm -O2 -g
clean:
	rm *.o *.out