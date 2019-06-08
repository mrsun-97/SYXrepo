#include <stdio.h>
#include <cuda_runtime.h>
#include <time.h>

__global__ void add_vec(int *a, int *b, int *c){
    int k = blockIdx.x * blockDim.x + threadIdx.x;
    c[k] = a[k] + b[k];
}

int repeat(int size){
    int i, a_host[size], b_host[size], c_host[size], c_fromgpu[size];
    for(i=0;i<size;i++){
        a_host[i] = i;
        b_host[i] = i/2-1;
    }

    int *a_dev, *b_dev, *c_dev;
    cudaEvent_t start, stop;
    float cputime, gputime;
    //clock_t time1, time2;

    //gpu
    int blocksize = 512;
    int blocknum = size/blocksize;
    blocknum += (blocksize*blocknum >= size) ? 0 : 1;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaMalloc(&a_dev, size*sizeof(int));
    cudaMalloc(&b_dev, size*sizeof(int));
    cudaMalloc(&c_dev, size*sizeof(int));
    dim3 dimBlock(blocksize, 1, 1);
    dim3 dimGrid(blocknum, 1, 1);

    cudaEventRecord(start, 0);
    cudaMemcpy(a_dev, a_host, size*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_dev, b_host, size*sizeof(int), cudaMemcpyHostToDevice);


    add_vec<<<dimGrid, dimBlock>>>(a_dev, b_dev, c_dev);
    cudaEventRecord(stop, 0);
    
    cudaMemcpy(c_fromgpu, c_dev, size*sizeof(int), cudaMemcpyDeviceToHost);

    cudaEventSynchronize(start);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gputime, start, stop);
    //cudaEventDestory(start);
    //cudaEventDestory(stop);
    cudaFree(a_dev);
    cudaFree(b_dev);
    cudaFree(c_dev);
    //cudaThreadExit();

    //cpu
    //time1 = clock();
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);
    for(i=0;i<size;i++){
        c_host[i] = a_host[i]+b_host[i];
    }
    //time2 = clock();
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(start);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&cputime, start, stop);
    //cputime = (time2 - time1)/(float)CLOCKS_PER_SEC;

    //check
    for(i=0;i<size;i++){
        if(c_host[i] != c_fromgpu[i]){
            printf("error occurs while calculating, outputs do not match\n");
            break;
        }
    }

    printf("size: %.1E,  gpu: %f,  cpu: %f,  rate: %f\n", (float)size, gputime, cputime, cputime/gputime);
    return 1;
}

int main(){

    int arraysize[] = {100000, 200000, 1000000, 2000000, 10000000, 20000000};
    int ii;

    for(ii=0;ii<6;ii++){
        repeat(arraysize[ii]);
    }
    return 0;
}