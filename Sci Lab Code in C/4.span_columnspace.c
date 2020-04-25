#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int forward_elimination(int n,int o,float a[n][o]){
    int c=0;
    for(int i=0;i<n-1;i++){
        if(a[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(a[m][i]!=0){
                    for(int b=0;b<o;b++){
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
            for(int j=0;j<o;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
    printf("\nFinal Matrix\n");
   for(int i=0;i<n;i++){
       if (a[i][i]!=0) c++;
        for(int j=0;j<o;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    return c;
    
    
}

void gauss_elimination(int n,int m,float a[n][m]){
    int res = forward_elimination(n,m,a);
    printf("Pivots:%d",res);
}

int main(){
    int n,m;
    printf("n m :");
    scanf("%d",&n);
    scanf("%d",&m);
    float a[n][m];
    printf("Enter the elements:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%f",&a[i][j]);
        }
    }
   /*for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    */
   struct timespec start, end; 
   clock_gettime(CLOCK_REALTIME, &start);
    gauss_elimination(n,m,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent : %lf\n",n,
            time_elapsed(start, end));
    return 0;
}