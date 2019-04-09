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
    int w;
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
                t[i].w = graph[u][v];
                i++;
            }  
        }

    }
    *s = i;
    //printf("\n");
}

void sort_by_weight(int (*graph)[MAX], int n, tuple *tt, int *ss)
{
    //tuple *tt = (tuple *)malloc(sizeof(tuple));
    //int ss;
    all_edges(graph, n, tt, ss);
    int i, j;
    for(i=0; i<*ss; i++)
    {
        printf("((%d, %d, %d))\t", tt[i].x, tt[i].y, tt[i].w);
        int min_ind = 0;
        for(j=i; j<*ss; j++)
        {
            min_ind = i;
            if(tt[j].w > tt[min_ind].w)
            {
                min_ind = j;               
            }
        }  
        int temp_w = tt[min_ind].w;
        int temp_x = tt[min_ind].x;
        int temp_y = tt[min_ind].y;
        tt[min_ind].w = tt[i].w;
        tt[min_ind].x = tt[i].x;
        tt[min_ind].y = tt[i].y;
        tt[i].w = temp_w;
        tt[i].x = temp_x;
        tt[i].y = temp_y; 
    }
    printf("\n");
}

void test_tuple()
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
    tuple *edges = (tuple *)malloc(sizeof(tuple));
    int size;
    sort_by_weight(graph, n, edges, &size);
    int i;
    for(i=0; i<size; i++)
        printf("(%d %d %d)\t", edges[i].x, edges[i].y, edges[i].w);
    printf("\n");
    
}

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
    test_tuple();
}