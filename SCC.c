#include<stdio.h>
#include<stdlib.h>
#define MAX 20
typedef struct node
{
    /* data */
    int val;
    struct node *next;
}nodes;

void create_graph(nodes *graph[], int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        graph[i] = NULL;
    }
    printf("Graph created of %i vertex.\n", i);
}

void add_edge(nodes *graph[], int u, int v)
{
    nodes *new_node = (nodes *)malloc(sizeof(nodes));
    new_node->next = NULL;
    new_node->val = v;

    if(graph[u] == NULL)
    {
        graph[u] = new_node;
    }
    else
    {
        nodes *curr = graph[u];
        while(curr->next != NULL)
            curr = curr -> next;
        curr->next = new_node;


    }
    //printf("\nEdge added %d ~> %d.", u, v);
    
}



void transpose(nodes *graph[], int n, nodes **Tgraph)
{
    int i;
    for(i=0;i<n;i++)
    {
        Tgraph[i] = NULL;
    }
    for(i = 0; i < n; i++)
    {
        nodes *curr = graph[i];
        while(curr != NULL)
        {
            add_edge(&*Tgraph, curr->val, i);
            curr = curr -> next;
        }
        
    }
}


void print_graph(nodes *graph[], int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("\n%d. ", i);
        if(graph[i] == NULL)
        {
            printf("NULL");
        }
        else
        {
            nodes *curr = graph[i];
            while(curr != NULL)
            {
                printf("[%d]-> ", curr->val); 
                curr = curr -> next;
            }
            printf("NULL");      
        }
        //printf("\n");
        
    }
}

/* 
white 0
grey  1
black 2
*/

int color[MAX];
int t;
int d[MAX];
int pi[MAX];
int f[MAX];
void dfs_visit(nodes *graph[], int u)
{
    color[u] = 1;
    t = t + 1;
    d[u] = t;
    if(graph[u] != NULL)
    {
        nodes *curr = graph[u];
        while(curr != NULL)
        {
            //getchar();
            int v = curr->val;
            //printf("\nDEBUG: from %d to %d\n", u, v); 
            //printf("\nDEBUG: color[%d]\n", color[u]);
            if(color[v] == 0)
            {
                pi[v] = u;
                printf("[%d] ~> [%d]\n", u, v);
                dfs_visit(&*graph, v);
            }
            //getchar();
            curr = curr -> next;
            //getchar();
        }
        color[u] = 2;
        t = t + 1;
        f[u] = t;

    }
}

void dfs(nodes *graph[], int n)
{
    int u;
    for(u=0;u<n;u++)
    {
        color[u] = 0;
        pi[u] = -1;
    }
    t = 0;
    for(u=0;u<n;u++)
    {
        if(color[u] == 0)
        {
            printf("[[%d]]\n", u);
            dfs_visit(&*graph, u);
        }
            
    }
}

int getMAX(int a[], int n)
{
    int i, ind=0;
    int M = a[0];
    for(i=0;i<n;i++)
    {
        if(M<a[i])
        {
            ind = i;
            M = a[i];
        }
            
    }
    //printf("\nDEBUGG::getMAX M=%d, ind=%d\n", M, ind);
    return ind;
}

void Tdfs(nodes *graph[], int n)
{
    int u, i, ff[MAX];
    for(i=0;i<n;i++)
        ff[i] = f[i];

    int gg[MAX];
    for(i=0;i<n;i++)
    {
        gg[i] = getMAX(ff, n);
        ff[gg[i]] = -2;
    }
    for(i=0;i<n;i++)
    {
        //getchar();
        u = gg[i];
        color[u] = 0;
        pi[u] = -1;
    }
    t = 0;
    //qsort(f, n, sizeof(int), cmpfunc);
    for(i=0;i<n;i++)
        printf("%d\t", gg[i]);
    printf("\n");
    for(i=0;i<n;i++)
    {
        u = gg[i];
        if(color[u] == 0)
        {
            printf("[[%d]]\n", u);
            dfs_visit(&*graph, u);
        }
            
    }
}


void print_all_param(int n)
{
    int i;
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("d[%d] = %d\t", i, d[i]);
        printf("f[%d] = %d\t", i, f[i]);
        printf("pi[%d] = %d\t", i, pi[i]);
        printf("color[%d] = %d\t", i, color[i]);
        
        printf("\n");
    }
}



void test(int n)
{
    int u, i, ff[MAX];
    for(i=0;i<n;i++)
        ff[i] = f[i];
    printf("VALUSES of ff\n");
    for(i=0;i<n;i++)
        printf("%d\t", ff[i]);
    int gg[MAX];
    for(i=0;i<n;i++)
    {
        gg[i] = getMAX(ff, n);
        ff[gg[i]] = -2;
        printf("DEBUG:: gg[%d] = %d; ff[gg[%d]] = %d\n", i, gg[i], i, ff[gg[i]]);
    }
    printf("VALUSES of gg\n");
    for(i=0;i<n;i++)
        printf("%d\t", gg[i]);

}

void examples()
{
    int n = 8;
    nodes *graph[MAX];
    nodes *Tgraph[MAX];


    //Example--1
    create_graph(&*graph, n);
    add_edge(&*graph, 0,1);
    add_edge(&*graph, 1,2);
    add_edge(&*graph, 1,6);
    add_edge(&*graph, 1,7);
    add_edge(&*graph, 2,3);
    add_edge(&*graph, 2,5);
    add_edge(&*graph, 3,2);
    add_edge(&*graph, 3,4);
    add_edge(&*graph, 4,4);
    add_edge(&*graph, 5,4);
    add_edge(&*graph, 5,6);
    add_edge(&*graph, 6,5);
    add_edge(&*graph, 7,6);
    add_edge(&*graph, 7,0);


    //EXAMPLE--2
    create_graph(&*graph, n);
    add_edge(&*graph, 0,1);
    add_edge(&*graph, 0,3);
    add_edge(&*graph, 1,2);
    add_edge(&*graph, 2,3);
    add_edge(&*graph, 3,1);
    add_edge(&*graph, 4,2);
    add_edge(&*graph, 4,5);
    add_edge(&*graph, 5,5);


    
}

int main(void)
{
    nodes *graph[MAX];
    nodes *Tgraph[MAX];
    int norm_d[MAX], norm_pi[MAX], norm_color[MAX], norm_f[MAX];
    int trans_d[MAX], trans_pi[MAX], trans_color[MAX], trans_f[MAX];


    //Pase your example here:: BEGIN---

    int n = 8;
    create_graph(&*graph, n);
    add_edge(&*graph, 0,1);
    add_edge(&*graph, 1,2);
    add_edge(&*graph, 1,6);
    add_edge(&*graph, 1,7);
    add_edge(&*graph, 2,3);
    add_edge(&*graph, 2,5);
    add_edge(&*graph, 3,2);
    add_edge(&*graph, 3,4);
    add_edge(&*graph, 4,4);
    add_edge(&*graph, 5,4);
    add_edge(&*graph, 5,6);
    add_edge(&*graph, 6,5);
    add_edge(&*graph, 7,6);
    add_edge(&*graph, 7,0);

    //--- END --
    
    //printf("\n\n -----------ORIGINAL GRAPH---------");
    //print_graph(&*graph, n);
    transpose(&*graph, n, *&Tgraph);
    //printf("\n\n -----------TRANSPOSE GRAPH---------");
    //print_graph(*&Tgraph, n);
    
    dfs(&*graph, n);
    //print_all_param(n);

    int i;
    for(i=0;i<n;i++)
    {
        norm_d[i] = d[i];
        norm_f[i] =f[i];
        norm_pi[i] = pi[i];
        norm_color[i] = color[i];
    }

    //test(n);
    
    Tdfs(&*Tgraph, n);
    //print_all_param(n);

    for(i=0;i<n;i++)
    {
        trans_d[i] = d[i];
        trans_f[i] =f[i];
        trans_pi[i] = pi[i];
        trans_color[i] = color[i];
    }

    int p, count = 0;
    for(p=0;p<n;p++)
    {
        if(pi[p] == -1)
            count += 1;

    }
    printf("\nNUmber of strongly connected component is %d\n", count);
    return 1;
}