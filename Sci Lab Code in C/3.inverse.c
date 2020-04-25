#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int swap_rows(int n,float a[n][2*n],int pos)
{
	int temp[2*n+1];
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

int main()
{
		 int i,j,k,n;
		 printf("Enter order of matrix: ");
		 scanf("%d", &n);
		 float a[n+1][2*n+1],ratio;
		 printf("Enter coefficients of Matrix:\n");
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
				scanf("%f", &a[i][j]);
			  }
		 }
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
		 printf("\nInverse Matrix is:\n");
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	printf("%0.3f\t",a[i][j]);
			  }
			  printf("\n");
		 }
		 return(0);
}
