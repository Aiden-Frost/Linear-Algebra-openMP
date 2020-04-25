#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>


float determinant(float **a, float k)
{
  float s = 1, det = 0, **b;
  b=malloc(sizeof(float*)*k);
  for(int i=0;i<k;i++){
    b[i]=(float*)malloc(sizeof(float*) * k);
  }
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }
 
    return (det);
}

/*Finding transpose of matrix*/ 
float **transpose(float **num, float **fac, float r)
{
  int i, j;
  float b[25][25],d;
    float **inverse;
    inverse=malloc(sizeof(float*)*r);
    for(int i=0;i<r;i++){
        inverse[i]=(float*)malloc(sizeof(float*) * r);
    }
 
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinant(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse[i][j] = b[i][j] / d;
        }
    }
    /*
   printf("\n\n\nThe inverse of matrix is : \n");
 
   for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         printf("\t%f", inverse[i][j]);
        }
    printf("\n");
     }*/
    return inverse;
}

float **cofactor(float **num, int f)
{
 float **b, **fac;
 b=malloc(sizeof(float*)*f);
 fac=malloc(sizeof(float*)*f);
 for(int i=0;i<f;i++){
    b[i]=(float*)malloc(sizeof(float*) * f);
    fac[i]=(float*)malloc(sizeof(float*) *f);
 }
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  return transpose(num, fac, f);
}


float **multiplier(int r1, int c1, int r2, int c2,float **first, float **second) 
{
    float **mult;
    mult=malloc(sizeof(float*)*r1);
    for(int i=0;i<r1;i++)
        mult[i]=(float*)malloc(sizeof(float*)*c2);
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            mult[i][j] = 0;
        }
    }

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            for (int k = 0; k < c1; ++k) {
                mult[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    /*
    for (int i=0 ; i<r1 ; i++){
        for(int j=0 ; j<c2 ; j++){
            printf("%0.3f ",mult[i][j]);
        }
        printf("\n");
    }
    */
    return mult;
}


int main(){
    float **a;
    float **b;
    int eqns,features;
    printf("Enter the number of equations and features\n");
    scanf("%d %d",&eqns,&features);
    a=malloc(sizeof(float*)*eqns);
    b=malloc(sizeof(float*)*eqns);
    for(int i=0;i<eqns;i++){
        a[i]=(float*)malloc(sizeof(float*) * (features+1));
        b[i]=(float*)malloc(sizeof(float*));
    }
    printf("Enter the values in the format x1 x2... xn y\n");
    for(int i=0;i<eqns;i++){
        for(int j=0;j<=(features+1);j++){
            if(j==0){
                a[i][j]=1;
            }
            else{
                float temp;
                scanf("%f",&temp);
                if(j==(features+1))
                    b[i][0]=temp;
                else{
                    a[i][j]=temp;
                }
            }
        }
    }/*
    for(int i=0;i<eqns;i++){
        for(int j=0;j<=features;j++){
            printf("%3.1f ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<eqns;i++){
        printf("%3.1f ",b[i][0]);
    }*/
    float **at;
    at=malloc(sizeof(float*)*(features+1));
    for(int i=0;i<eqns;i++){
        at[i]=(float*)malloc(sizeof(float*) * eqns);
    }
    for(int i=0;i<eqns;i++){
        for(int j=0;j<=features;j++){
            at[j][i]=a[i][j];
        }
    }
    printf("\n");
    /*
    for(int i=0;i<=features;i++){
        for(int j=0;j<eqns;j++){
            printf("%3.1f ",at[i][j]);
        }
        printf("\n");
    }*/
    float **result1=multiplier(features+1,eqns,eqns,features+1,at,a);
    /*
    for(int i=0;i<=features;i++){
        for(int j=0;j<=features;j++){
            printf("%3.1f ",result1[i][j]);
        }
        printf("\n");
    }
    */
    float **result2=multiplier(features+1,eqns,eqns,1,at,b);
    /*
    for(int i=0;i<=features;i++){
        for(int j=0;j<1;j++){
            printf("%3.1f ",result2[i][j]);
        }
        printf("\n");
    }*/
    float **result=cofactor(result1,features+1);
    /*
    for(int i=0;i<=features;i++){
        for(int j=0;j<=features;j++){
            printf("%3.1f ",result[i][j]);
        }
        printf("\n");
    }
    */
    float **result_final=multiplier(features+1,features+1,features+1,1,result,result2);
    printf("The solutions for the least squares line are:\n");
    for(int i=0;i<features;i++){
        printf("%3.3fx%d + ",result_final[i][0],i);
    }
    printf("%3.3fx%d",result_final[features][0],features);
    return 0;
}