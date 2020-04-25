#include <stdio.h>
//1
/*
void create_table(long long int *table,int n)
{
	table[0] = 1;
	table[1] = 2;
	table[2] = 4;
	for (int i=3 ; i<n ; i++)
	{
		table[i] = -1;
	}
}


long long int not_consective_ones(long long int *table,int n)
{
	if (table[n] != -1)
	{
		return table[n];
	}
	else
	{
		table[n] = not_consective_ones(table,n-1) + not_consective_ones(table,n-2) + 						  not_consective_ones(table,n-3);
	}
	return table[n];
}

int main()
{
	int n;
	scanf("%d",&n);
	long long int table[n+1];
	create_table(table,n+1);
	long long int res = not_consective_ones(table,n);
	res = pow(2,n) - res;
	printf("%lld",res);
	return 0;
}


//2
void create_minimum_table(int *table,int n)
{
	table[0] = 0;
	for (int i=1 ; i<n ; i++)
	{
		table[i] = -1;
	}
}

int minimum_number_of_coins(int *coins,int total)
{
	int table[total+1];
	create_minimum_table(table,total+1);
	for (int i=1 ; i<=total ; i++)
	{
		for (int j=0 ; j<3 ; j++)
		{
			if ( coins[j] <= i && table[i-coins[j]] != -1)
			{
				int old_value = table[i];
				int new_value = 1 + table[i-coins[j]];
				if ( old_value == -1 || new_value < old_value)
				{
					table[i] = new_value;
				}
			}
		}
	}
	return table[total];
}

int main()
{
	int coins[3];
	int total;
	int n;
	scanf("%d",&n);
	for (int i=0 ; i<n ; i++)
	{
		scanf("%d %d %d %d",&coins[0],&coins[1],&coins[2],&total);
		int result = minimum_number_of_coins(coins,total);
		if (result == -1)
		{
			printf("ERROR\n");
		}
		else
		{
			printf("%d\n",result);
		}
	}
	return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to calculate the minimum number of coins required to make the change for the amount of 'n' rupees using an infinite supply of coins of denominations a,b and c where a<b<c

int min = INT_MAX;

int coin_change(int a,int b,int c,int n);

int coin_change(int a,int b,int c,int n){

	if(n==0){
		return 0;
	}

	else if(n<a){
		return min;
	}

    else if(n==a || n==b || n==c){
		return 1;
	}

    else{

		if(n<b){

			if(n%a==0){
				return (n/a);
			}

			else{
				return min;
			}
		}

        else{

			int result;

			//Creating and using 2 1-D arrays of size (n+1)

			int* arr1 = (int*)malloc(sizeof(int)*(n+1));
			int* arr2 = (int*)malloc(sizeof(int)*(n+1));
			for (int i=0 ; i<n+1 ; i++)
			{
				arr1[i] = min;
				arr2[i] = min;
			}
            for(int i=0;i<n+1;++i){
				if(i%a==0){
					arr1[i] = (i/a);
				}
			}

            for(int i=0;i<b;++i){
				arr2[i] = arr1[i]; //Copying the values of the first array into the second 
			}

			arr2[b] = 1;

            for(int i=b+1;i<n+1;++i){
				int d = arr2[i-b];
				int e = arr1[i];
				//if (i==n)	printf("%d %d %d %d\n",d,i,b,arr1[i-b]);
				if(d==min){
					arr2[i] = e;
				}

				else if(e==min){
					arr2[i] = d+1;
				}

                else{
					
					//Cool ternary way to do it - arr2[i] = e<(d+1)?e:(d+1);

					if(e<(d+1)){
						arr2[i] = e;
					}

					else{
						arr2[i] = d+1;
					}
				}

			}

            if(n<c){
				result = arr2[n];
			}
			
			else{

				for(int i=b;i<n+1;++i){
					arr1[i] = arr2[i];
				}

				arr1[c] = 1;

                for(int i=c+1;i<n+1;++i){
					int f = arr1[i-c];
					int g = arr2[i];
				

					if(f==min){
						arr1[i] = g;
					}

                    else if(g==min){
						arr1[i] = f+1;
					}

					else{

						//Lets be cool 
						arr1[i] = g<(f+1)?g:(f+1);

					}

				}

                result = arr1[n];
			}

			return result;
			free(arr1);
			free(arr2);

		}
	}
}

// Driver function 
int main(){

	int a,b,c,n;
	scanf("%d %d %d %d",&a,&b,&c,&n);
    int res = coin_change(a,b,c,n);

		if(res==min){
			printf("ERROR\n");
		}

        else{
			printf("%d\n",res);
		}

}