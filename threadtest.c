#include<stdio.h>
#include<omp.h>

int main(){
    const int nt=omp_get_max_threads();
    printf("OpenMP with %d threads\n",nt);

    #pragma omp parallel
    {
        printf("Hello world from thread %d\n", omp_get_thread_num());
    }
}