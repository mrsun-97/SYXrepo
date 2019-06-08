#include <stdio.h>
#include <mpi.h>

double f1(double x){
    return 4.0/(x*x+1.0);
}

double simpson(double l_range, double r_range, double (*func)(double), int n){
    double step = (r_range-l_range)/n;
    double A[n], B[n];
    int i;
    for(i=0;i<n;i++){
        A[i] = func( l_range+i*step );
        B[i] = func( l_range+(i+0.5)*step );
    }
    A[0] += func( r_range );
    A[0] /= 2;
    double sum1=0, sum2=0;
    for(i=0;i<n;i++){
        sum1 += A[i];
        sum2 += B[i];
    }
    sum1 = (2*sum1+4*sum2)/6*step;
    return sum1;
}

int main(){

    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i, num = 200;
    int inner_num = 16;
    double step = 1.0/num;
    double sum = 0;
    for(i=rank;i<num;i+=size){
        //辛普森积分
        sum += simpson(i*step, (i+1)*step, &f1, inner_num);
    }

    if(rank == 0){
        double tmp[size];
        for(i=1;i<size;i++){
            MPI_Recv(&tmp[i], 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        tmp[0] = sum;
        for(i=0,sum=0;i<size;i++){
            sum += tmp[i];
        }
        printf("--> PI = %.14lf\n total steps:\t%d\n total cores:\t%d\n", sum, num*inner_num, size);

    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    //printf("%d finished.\n", rank);
    return 0;

}