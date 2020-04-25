#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int swap_rows(int n,float a[n][2*n],int pos)
{
	int temp[2*n];
	for (int i=pos+1;i<=n;i++){
		if (a[i][i]!=0){
			for (int j=0;j<=2*n;j++){
				temp[j] = a[i][j];
				a[i][j] = a[pos][j];
				a[pos][j] = temp[j];
			}
			return 1;
		}
	}
	return 0;
}

void inverse(int n,float a[n+1][2*n+1],float b[n+1][n+1])
{
    int i,j,k;
    float ratio;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i==j)
            {
                a[i][j+n] = 1;
            }
            else
            {
                a[i][j+n] = 0;
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        if(a[i][i] == 0.0)
        {
            if (swap_rows(n,a,i))  continue;
            printf("Mathematical Error!");
            exit(0);
        }
        for(j=1;j<=n;j++)
        {
            if(i!=j)
            {
                ratio = a[j][i]/a[i][i];
                for(k=1;k<=2*n;k++)
                {
                    a[j][k] = a[j][k] - ratio*a[i][k];
                }
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
            a[i][j] = a[i][j]/a[i][i];
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
            b[i][j-n] = a[i][j];
        }

    }
}

void multiplyMatrices(int r1, int c1, int r2, int c2,float first[r1+1][c1+1], float second[r2+1][c2+1], float mult[r1+1][c2+1] ) 
{

    for (int i = 1; i <= r1; ++i) {
        for (int j = 1; j <= c2; ++j) {
            mult[i][j] = 0;
        }
    }

    for (int i = 1; i <= r1; ++i) {
        for (int j = 1; j <= c2; ++j) {
            for (int k = 1; k <= c1; ++k) {
                mult[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    for (int i=1 ; i<=r1 ; i++){
        for(int j=1 ; j<=c2 ; j++){
            printf("%0.3f ",mult[i][j]);
        }
        printf("\n");
    }
}

int main()
{
		 int i,j,k,n,m,n1,m1;
		 printf("Enter order of matrix A ( nxm ): ");
		 scanf("%d", &n);
         scanf("%d", &m);
		 float input[n+1][m+1],trans[m+1][n+1],a[m+1][2*m+1],b[n+1][m1+1],inv[m+1][m+1],mul[m+1][m+1],res[n+1][m1+1],final_res[m+1][m1+1];
		 printf("Enter coefficients of Matrix A:\n");
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=m;j++)
			  {
				scanf("%f", &input[i][j]);
                trans[j][i] = input[i][j];
			  }
		 }
        printf("Enter order of matrix B ( n ): ");
        scanf("%d", &m1);
        printf("Enter coefficients of Matrix B:\n");
        for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=m1;j++)
			  {
				scanf("%f", &b[i][j]);
			  }
		 }
        multiplyMatrices(m,n,n,m,trans,input,mul);
        for (int i=1 ; i<=m ; i++){
            for (int j=1 ; j<=m ; j++){
                a[i][j] = mul[i][j];
            }
        }
        inverse(m,a,inv);
        multiplyMatrices(m,n,n,m1,trans,b,res);
        printf("Projection by least Square:\n");
        multiplyMatrices(m,m,m,m1,inv,res,final_res);
}
