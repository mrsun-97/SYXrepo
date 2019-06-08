mpiicc main.c -lm -O -o 2.out && mpirun -n 4 ./2.out
mpiicc pi.c -O -o pi.out && mpirun -n 4 ./pi.out