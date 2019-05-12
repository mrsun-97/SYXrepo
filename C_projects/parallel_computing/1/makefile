
CC=icc

psrs: main.c main.h
	$(CC) $< -o $@.out -qopenmp -lm -O2 -g
clean:
	rm *.o *.out
