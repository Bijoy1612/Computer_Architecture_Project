#pragma GCC optimize("O1","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <windows.h>
#include <x86intrin.h>


void *benchInt(void* vargp)
{   if (vargp!=NULL)    // Lock thread to a single Core
        SetThreadAffinityMask(GetCurrentThread(), GetCurrentProcessorNumber());
    uint64_t i = 0;     // Declare 64 bit integer
    for(i = 1; i < 100000000000; i++){
        222%73*(i-9999);    // Integer operations: Increment, modulus, multiplication, subtraction
    }
    return NULL;
}

void *benchFloat(void* vargp)
{
    if (vargp!=NULL)
        SetThreadAffinityMask(GetCurrentThread(), GetCurrentProcessorNumber());
    double i;   // Declare 64 bit floating point number
    for(i = 0.5; i < 5000000000; i++){
        222/77.777777*(i-999);      // Float operations: Increment, division, multiplication, subtraction
    }
    return NULL;
}

void *benchPrime(void *vargp){      // Prime number calculation algorithm
    if (vargp!=NULL)
        SetThreadAffinityMask(GetCurrentThread(), GetCurrentProcessorNumber());
    int flag;
    uint32_t i, j;      // Declare 64 bit integers for for loop
    for(i=2; i<10000000; i++){  // All prime numbers upto 10000000
        flag = 1;   // flag for deciding if prime or not
        for(j = 2; j<sqrt(i)+1 ; j++){
            if(i%j == 0){
                flag = 0;
                break;      // break if number is divisible
            }
        }
    }
    return NULL;
}


double timeMS(struct timeval  tv1, struct timeval tv2){
    double s = (double)(tv1.tv_sec - tv2.tv_sec);   // Calulate time difference in seconds
    double us = (tv1.tv_usec - tv2.tv_usec)/1000000.0; // Calclulate time difference in Micro-seconds
    return (s+us);  // Add and return time
}

void stbench(){
    printf("\t\tRunning Benchmark...\n");
    struct timeval start, end;
    pthread_t thread[16]; // Create an array of threads to be created

    gettimeofday(&start, NULL); // Get Thread Starting Time
    pthread_create(&thread[0], NULL, benchInt, (void*)1); // Create a single thread
    pthread_join(thread[0], NULL); // Wait for thread termination
    gettimeofday(&end, NULL); // Get Thread Ending Time
    // Print total thread time
    printf("\t\tSingle Threaded Integer Arithmetic Time:\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    pthread_create(&thread[0], NULL, benchFloat, (void*)1);
    pthread_join(thread[0], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tSingle Threaded Floating point Arithmetic Time:\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    pthread_create(&thread[0], NULL, benchPrime, (void*)1);
    pthread_join(thread[0], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tSingle Threaded Prime Number Calculation Time:\t %.6fs\n", timeMS(end,start));
    system("pause");
}

void mtBench(int n){
    printf("\t\tRunning Benchmark...\n");
    struct timeval start, end;
    pthread_t thread[16]; // Create an array of threads to be created

    gettimeofday(&start, NULL);
    for(int i=0; i<n; i++)  // For loop for creating threads
        pthread_create(&thread[i], NULL, benchInt, NULL);
    for(int i=0; i<n; i++)  // For loop for terminating threads
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Integer Arithmetic Time(%dt):\t\t %.6fs\n", n, timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<n; i++)
        pthread_create(&thread[i], NULL, benchFloat, NULL);
    for(int i=0; i<n; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Floating point Arithmetic Time(%dt):\t %.6fs\n", n, timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<n; i++)
        pthread_create(&thread[i], NULL, benchPrime, NULL);
    for(int i=0; i<n; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Prime Number Calculation Time (%dt):\t %.6fs\n",n,timeMS(end,start));
    system("pause");
}

void benchAll(){
    printf("\t\tRunning Benchmark...\n");
    struct timeval start, end;
    pthread_t thread[16]; // Create an array of threads to be created

    gettimeofday(&start, NULL); // Get Thread Starting Time
    pthread_create(&thread[0], NULL, benchInt, (void*)1); // Create a single thread
    pthread_join(thread[0], NULL); // Wait for thread termination
    gettimeofday(&end, NULL); // Get Thread Ending Time
    // Print total thread time
    printf("\t\tSingle Threaded Integer Arithmetic Time:\t %.6fs\n", timeMS(end,start));


    gettimeofday(&start, NULL);
    for(int i=0; i<4; i++)  // For loop for creating threads
        pthread_create(&thread[i], NULL, benchInt, NULL);
    for(int i=0; i<4; i++)  // For loop for terminating threads
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Integer Arithmetic Time(4t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<8; i++)  // For loop for creating threads
        pthread_create(&thread[i], NULL, benchInt, NULL);
    for(int i=0; i<8; i++)  // For loop for terminating threads
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Integer Arithmetic Time(8t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<16; i++)
        pthread_create(&thread[i], NULL, benchInt, NULL);
    for(int i=0; i<16; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Integer Arithmetic Time(16t):\t %.6fs\n\n", timeMS(end,start));


    gettimeofday(&start, NULL);
    pthread_create(&thread[0], NULL, benchFloat, (void*)1);
    pthread_join(thread[0], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tSingle Threaded Floating point Arithmetic Time:\t\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<4; i++)
        pthread_create(&thread[i], NULL, benchFloat, NULL);
    for(int i=0; i<4; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Floating point Arithmetic Time(4t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<8; i++)
        pthread_create(&thread[i], NULL, benchFloat, NULL);
    for(int i=0; i<8; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Floating point Arithmetic Time(8t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<16; i++)
        pthread_create(&thread[i], NULL, benchFloat, NULL);
    for(int i=0; i<16; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Floating point Arithmetic Time(16t):\t %.6fs\n\n", timeMS(end,start));


    gettimeofday(&start, NULL);
    pthread_create(&thread[0], NULL, benchPrime, (void*)1);
    pthread_join(thread[0], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tSingle Threaded Prime Number Calculation Time:\t\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<4; i++)
        pthread_create(&thread[i], NULL, benchPrime, NULL);
    for(int i=0; i<4; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Prime Number Calculation Time (4t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<8; i++)
        pthread_create(&thread[i], NULL, benchPrime, NULL);
    for(int i=0; i<8; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Prime Number Calculation Time (8t):\t %.6fs\n", timeMS(end,start));

    gettimeofday(&start, NULL);
    for(int i=0; i<16; i++)
        pthread_create(&thread[i], NULL, benchPrime, NULL);
    for(int i=0; i<16; i++)
        pthread_join(thread[i], NULL);
    gettimeofday(&end, NULL);
    printf("\t\tMulti Threaded Prime Number Calculation Time (16t):\t %.6fs\n\n", timeMS(end,start));
    system("pause");
}

int main()
{
    printf("\t\t\t\tWELCOME TO THE BENCHMARK PROGRAM");
    int x;
    while(1) {
        printf("\n\n\t\tSelect Benchmark Mode:\n\n"
               "\t\t\t 1. Single Threaded Benchmark\n"
               "\t\t\t 2. Multi Threaded Benchmark (4 Threads)\n"
               "\t\t\t 3. Multi Threaded Benchmark (8 Threads)\n"
               "\t\t\t 4. Multi Threaded Benchmark (16 Threads)\n"
               "\t\t\t 5. All Benchmarks\n"
               "\t\t\t 0. Exit\n"
               "\t\t\t Select Mode: ");
        scanf("%d", &x);
        if(x == 1)
        {
            stbench();
        }
        else if(x == 2)
        {
            mtBench(4);
        }
        else if(x == 3)
        {
            mtBench(8);
        }
        else if(x == 4)
        {
            mtBench(16);
        }
        else if(x == 5)
        {
            benchAll();
        }
        else if(x == 0)
        {
            exit(0);
        }
        else
        {
            break;
        }
    }
    return 0;
}
