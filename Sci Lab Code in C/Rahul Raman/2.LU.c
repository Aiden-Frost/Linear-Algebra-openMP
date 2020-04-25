#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int lu(int n,float a[n][n+1]){
    float L[n][n];
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) L[i][j]=1.0f;
            else L[i][j]=0.0f;
        }
    }
    for(int i=0;i<n-1;i++){
        if(a[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(a[m][i]!=0){
                    for(int b=0;b<n+1;b++){
                        float temp= a[i][b];
                        a[i][b] = a[m][b];
                        a[m][b] = temp;
                    }
                    break;
                }
            }
            if(a[i][i]==0) return 0;
        }
        for(int k=1;k<n-i;k++){
            float l = a[i+k][i]/a[i][i];
            L[i+k][i] = l;
            for(int j=0;j<n+1;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
    printf("\n L :=\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",L[i][j]);
        }
        printf("\n");
    }
    printf("\n U :=\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    return 1;
    
    
}


int main(){
    int n;
    printf("Enter the number of unknown variables:");
    scanf("%d",&n);
    float a[n][n+1];
    float b[n][n+1];
    printf("Enter the elements:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%f",&a[i][j]);
            b[i][j] = a[i][j];
        }
    }

   struct timespec start, end; 
   clock_gettime(CLOCK_REALTIME, &start);
    lu(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on LU_Decomposition for %d variables: %lf\n",n,
            time_elapsed(start, end));
    printf("\nSecon TIme\n");
    lu(n,b);
    return 0;
}