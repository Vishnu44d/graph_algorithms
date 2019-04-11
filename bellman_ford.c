#include<stdio.h>
#include<stdlib.h>

#define MAX 20
#define INFINITY 999999
#define True 1
#define False 0

typedef struct tuple
{
    /* data */
    int x;
    int y;
}tuple;


// DEINATION of GRAPH (Adj. Matrix) :: BEGIN --
void create_graph(int (*graph)[MAX], int n)
{
    int i, j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            graph[i][j] = INFINITY;
    }
    printf("GRAPH created with number of Vertex: %d\n", n);
}

void add_edge(int (*graph)[MAX], int u, int v, int w)
{
    graph[u][v] = w;
    printf("Edge Added %d ~ %d with weight = %d\n", u, v, w);
}

void del_edge(int (*graph)[MAX], int u, int v)
{
    graph[u][v] = INFINITY;
    printf("Edge Deleted %d ~ %d \n", u, v);
}

void get_adj(int (*graph)[MAX], int n, int u, int *adj, int *size)
{
    //size is the number of vertex adjecent to `u`
    int i, j=0;
    for(i=0;i<n;i++)
    {
        if(graph[u][i] != INFINITY)
        {
            adj[j] = i;
            j++;
        }
            
    }
    *size = j;
        
}

void print_graph(int (*graph)[MAX], int n)
{
    int i, j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(graph[i][j] == INFINITY)
                printf("INF\t");
            else
                printf("%d\t",graph[i][j]);
        }
            
        printf("\n");
    }
}

void all_edges(int (*graph)[MAX], int n, tuple *t, int *s)
{
    int u, v, i=0;
    for(u=0;u<n;u++)
    {
        for(v=0;v<n;v++)
        {
            if(graph[u][v] != INFINITY)
            {
                //printf("(x, y) = (%d, %d)\t", u, v);
                t[i].x = u;
                t[i].y = v;
                i++;
            }  
        }

    }
    *s = i;
    //printf("\n");
}

void print_all_edges(int (*graph)[MAX], int n)
{
    tuple *t = (tuple *)malloc(sizeof(tuple));
    int s;
    all_edges(graph, n, t, &s);
    int i;
    for(i=0; i<s; i++)
        printf("(%d, %d)\t", t[i].x, t[i].y);
    printf("\n");
}

// DEINATION of GRAPH (Adj. Matrix) :: END --

int d[MAX];
int pi[MAX];

int bellman_ford(int (*graph)[MAX], int n, int s)
{
    int u, v;
    for(u=0; u<n; u++)
    {
        d[u] = INFINITY;
        pi[u] = -1;
    }
    d[s] = 0;
    int i, j; 

    tuple *edges = (tuple *)malloc(sizeof(tuple));
    int size;
    all_edges(graph, n, edges, &size);
    for(j=0;j<n-1;j++)
    {
        for(i=0;i<size;i++)
        {
            u = edges[i].x;
            v = edges[i].y;
            if(d[v] > d[u] + graph[u][v])
            {
                d[v] = d[u] + graph[u][v];
                pi[v] = u;
            }
        }
    }

    for(i=0;i<size;i++)
    {
        u = edges[i].x;
        v = edges[i].y;
        if(d[v] > d[u] + graph[u][v])
        {
            return False;
        }
    }
    return True;
}

void print_all_param(int n)
{
    int i;
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("d[%d] = %d\t", i, d[i]);
        printf("pi[%d] = %d\t", i, pi[i]);
        
        printf("\n");
    }
}

void example1()
{
    int n=5;
    int graph[MAX][MAX];
    create_graph(graph, n);

    add_edge(graph, 0, 1, 6);
    add_edge(graph, 0, 4, 7);
    add_edge(graph, 1, 2, 5);
    add_edge(graph, 1, 4, 8);
    add_edge(graph, 1, 3, -4);
    add_edge(graph, 2, 1, -1);
    add_edge(graph, 3, 2, 7);
    add_edge(graph, 3, 0, 2);
    add_edge(graph, 4, 2, -3);
    add_edge(graph, 4, 3, 9);

    print_graph(graph, n);
    print_all_edges(graph, n);
    
    int isFisible;
    isFisible = bellman_ford(graph, n, 0);
    print_all_param(n);
    if(isFisible == True)
    {
        printf("POSSIBLE\n");
        
    }
    else
    {
        printf("CONTAINS NEGATIVE CYCLES\n");
    }
}

int main(void)
{
    example1();
    return 1;
}