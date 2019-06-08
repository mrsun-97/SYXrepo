CC=nvcc

add: main.cu
	$(CC) $< -o $@.out -g -O2

mp: mp.cu
	$(CC) $< -o $@.out -g -O2

clean:
	rm *.out *.o

.PHONY: clean