#include<stdio.h>
#define MAX 20

void make_set(int n, int *p)
{
    int i;
    for(i=0;i<n;i++)
        p[i] = -1;
}

int find_set(int *p, int u)
{
    int i = p[u], j;
    if(i ==-1)
    {
        //printf("%d \n", u);
        return u;
    }
        
    else
    {
        while(i != -1)
        {
            j = i;
            i = p[i];
        }
        //printf("%d ~> %d\n", j, p[j]);
        return j;
    }  
}

void make_union(int *p, int u, int v)
{
    //printf("UNION OP {%d} U {%d}\n", u, v);
    int pu, pv;
    pu = find_set(p, u);
    pv = find_set(p, v);
    if(pu == pv)
        printf("Both { %d(%d) U %d(%d) } belongs to same set. (Doing noting)\n", u, pu, v, pv);
    else
    {
        //printf("%d %d\n", pv, pu);
        p[pv] = u;

        printf("Union success { %d(%d) U %d(%d) }\n", u, pu, v, pv);
    } 
}


int main(void)
{
    int n=8, p[MAX];
    make_set(n, p);
    make_union(p, 1, 2);
    make_union(p, 0, 3);
    make_union(p, 1, 0);
    make_union(p, 4, 5);
    make_union(p, 6, 7);
    make_union(p, 0, 6);
    //make_union(p, 5, 6);
    //make_union(p, 0, 6);
    int i;
    printf("BEFORE PATH COMPRESSION\n");
    for(i=0;i<n;i++)
    {
        //printf("%d\n", i);
        printf("%d\t", p[i]);
    }
    printf("\n");

    // -- Compressing path BEGIN --
    int kl = 0;
    for(;kl<n;kl++)
    {
        int pkl = find_set(p, kl);
        //printf("representator of %d is %d\n", kl, pkl);
        if(p[kl] != -1)
            p[kl] = pkl;
    }
    // -- Compressing path END --

    printf("AFTER PATH COMPRESSION\n");
    for(i=0;i<n;i++)
    {
        //printf("%d\n", i);
        printf("%d\t", p[i]);
    } 
    printf("\n");
    return 1;
}