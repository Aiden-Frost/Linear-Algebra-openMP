#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int forward_elimination(int n,float a[n][n+1]){
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
            for(int j=0;j<n+1;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
    printf("\nFinal Matrix\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    return 1;
    
    
}

void back_substitution(int n,float a[n][n+1]){
    float sol[n]; 
	for (int i = n-1; i >= 0; i--) 
	{ 
		sol[i] = a[i][n]; 
		for (int j=i+1; j<n; j++) 
		    sol[i] -= a[i][j]*sol[j]; 
		sol[i] = sol[i]/a[i][i]; 
	} 

	printf("\nSolution for the system:\n"); 
	for (int i=0; i<n; i++) 
		printf("%f\n", sol[i]); 
} 


void gauss_elimination(int n,float a[n][n+1]){
    int res = forward_elimination(n,a);
    if(res == 0) printf("\nSingular");
    else{
        int lhs=0;
        int rhs = 1 && a[n-1][n];
        for(int z=0;z<n;z++){
            lhs = lhs || (int)a[n-1][z];
        }
        if(lhs==0 && rhs==0) printf("\nSingular and Infinitely many Solution");
        else if(lhs==0 && rhs!=0) printf("\nSingular and No Solution");
        else {
            back_substitution(n,a);
            printf("\nNon Singular and unique solution");
        }
    }
}



int main(){
    int n;
    printf("Enter the number of unknown variables:");
    scanf("%d",&n);
    float a[n][n+1];
    printf("Enter the elements:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
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
    gauss_elimination(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on gaussian_elimination for %d variables: %lf\n",n,
            time_elapsed(start, end));
    return 0;
}