#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#define INFINITY 999999
#define MAX 20



int weight[MAX][MAX],completed[MAX],n,cost=0;
 

struct timespec start, end;

void initial()
{
    FILE *fp;
    fp = fopen("tsp_brute.csv", "w");
    fprintf(fp, "%s,%s\n", "length", "time");
    fclose(fp);
}

int gen_rand()
{
    //srand(29);
	int max = 15;
	int min = 2;
    int r = rand();
    r = r % (max - min);
    return r + min;
}

void takeInput(int n)
{
	int i,j;
 
	//printf("Enter the number of villages: ");
	//scanf("%d",&n);
 
	//printf("\nEnter the Cost Matrix\n");
 
	for(i=0;i < n;i++)
	{
		//printf("\nEnter Elements of Row: %d\n",i+1);
 
		for( j=0;j < n;j++)
			weight[i][j] = gen_rand();
 
		completed[i]=0;
	}
 
	printf("\n\nThe cost list is:");
 
	for( i=0;i < n;i++)
	{
		printf("\n");
 
		for(j=0;j < n;j++)
			printf("\t%d",weight[i][j]);
	}
}

int least(int c)
{
	int i,nc=INFINITY;
	int min=INFINITY,kmin;
 
	for(i=0;i < n;i++)
	{
		if((weight[c][i]!=0)&&(completed[i]==0))
			if(weight[c][i]+weight[i][c] < min)
			{
				min=weight[i][0]+weight[c][i];
				kmin=weight[c][i];
				nc=i;
			}
	}
	if(min!=INFINITY)
		cost+=kmin;
 
	return nc;
}

void mincost(int city)
{
	int i,ncity;
 
	completed[city]=1;
 
	printf("%d--->",city+1);
	ncity=least(city);
 
	if(ncity==INFINITY)
	{
		ncity=0;
		printf("%d",ncity+1);
		cost+=weight[city][ncity];
 
		return;
	}
 
	mincost(ncity);
}

void driver(int n)
{
	takeInput(n);


	long long int s1, s2, e1, e2;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    s1 = start.tv_nsec;
    s2 = start.tv_sec;

	mincost(0);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    e1 = end.tv_nsec;
    e2 = end.tv_sec;
    long long int t = (e1 - s1) + (e2 - s2) * 1000000000;
	printf("\n\nMinimum cost is %d\n ",cost);
    printf("\ntime taken is %lld\n", t);
    FILE *fp;
    fp = fopen("tsp_brute.csv", "a");
    fprintf(fp, "%d,%lld\n", n, t);
    fclose(fp);
}

int main()
{
	int n = 5;
	driver(n);
	
 
	return 0;
} 