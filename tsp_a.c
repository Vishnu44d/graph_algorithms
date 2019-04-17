#define _GNU_SOURCE
#include<stdio.h>
#include<time.h>
#include<sched.h>
 
int ary[10][10],completed[10],n,cost=0;
 
void takeInput(int x)
{
	int i,j;
  	n=x;
	//printf("Enter the number of villages: ");
	//scanf("%d",&n);
 	
	//printf("\nEnter the Cost Matrix\n");
 
	for(i=0;i < n;i++)
	{
		//printf("\nEnter Elements of Row: %d\n",i+1);
 
		for( j=0;j < n;j++)
			ary[i][j]=rand()%100;
 
		completed[i]=0;
	}

 
//	printf("\n\nThe cost list is:");
/* 
	for( i=0;i < n;i++)
	{
		printf("\n");
 
		for(j=0;j < n;j++)
			printf("\t%d",ary[i][j]);
	}*/
}
 
void mincost(int city)
{
	int i,ncity;
 
	completed[city]=1;
 
//	printf("%d--->",city+1);
	ncity=least(city);
 
	if(ncity==999)
	{
		ncity=0;
//		printf("%d",ncity+1);
		cost+=ary[city][ncity];
 
		return;
	}
 
	mincost(ncity);
}
 
int least(int c)
{
	int i,nc=999;
	int min=999,kmin;
 
	for(i=0;i < n;i++)
	{
		if((ary[c][i]!=0)&&(completed[i]==0))
			if(ary[c][i]+ary[i][c] < min)
			{
				min=ary[i][0]+ary[c][i];
				kmin=ary[c][i];
				nc=i;
			}
	}
 
	if(min!=999)
		cost+=kmin;
 
	return nc;
}
 
int main()
{
	srand(time(NULL));
    	cpu_set_t  mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);
	int size = 5;
	printf("size,time\n");
	while(size<=50){		
		struct timespec start, end; 
    		//clock_gettime(CLOCK_REALTIME, &start);	
		takeInput(size);
//		size+=10;
 		clock_gettime(CLOCK_REALTIME, &start);	
	//printf("\n\nThe Path is:\n");
		mincost(0); //passing 0 because starting vertex
 		clock_gettime(CLOCK_REALTIME, &end);
        	long long int time_taken; 
		time_taken = (end.tv_nsec - start.tv_nsec) ;
		time_taken+=(end.tv_sec - start.tv_sec)*1e9;
		printf("%d,%lld\n",size,time_taken);
		size+=5;		
	//printf("\n\nMinimum cost is %d\n ",cost);
 	}
	return 0;
}
