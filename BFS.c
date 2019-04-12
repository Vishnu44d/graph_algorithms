#include<stdio.h>
#include<stdlib.h>

#define MAX 20
#define INFINITY 999999
#define True 1
#define False 0

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

// DEINATION of GRAPH (Adj. Matrix) :: END --

//QUEUE :: BEGIN -- 

typedef struct node
{
    int value;
    struct node *next;
}node;

void enqueue(node **H, int v)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = v;
    new_node->next = NULL;
    if(*H == NULL)
        *H = new_node;
    else
    {
        node *curr = *H;
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = new_node;
        //printf("DEBUGG::NODE ADDED %d\n", curr->value);
    }
    
}

// if return -2 the empty queue

int dequeue(node **H)
{
    if(*H == NULL)
        return -2;
    else
    {
        int v;
        node *curr = *H;
        v = curr->value;
        *H = curr->next;
        return v;
    }   
}

int is_empty(node **H)
{
    if(*H == NULL)
        return True;
    return False;
}

void see_queue(node *H)
{
    if(H == NULL)
        printf("NULL\n");
    else
    {
        node *curr = H;
        while(curr != NULL)
        {
            printf("[%d] -> ", curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
            
    }
}

// QUEUE :: END --


// BFS :: BEGIN --

/*
color[u] = 0 undiscovered
color[u] = 1 discovered
color[u] = 2 explored
*/

int t;
int color[MAX];
int d[MAX];
int pi[MAX];
 
void BFS(int (*graph)[MAX], int n, int s)
{
    int u;
    for(u=0; u<n; u++)
    {
        color[u] = 0;
        d[u] = INFINITY;
        pi[u] = -1;
    }
    color[s] = 1;
    d[s] = 0;
    node *Q = NULL; 
    enqueue(&Q, s);
    while(is_empty(&Q) == False)
    {
        u = dequeue(&Q);
        int *adj = (int *)malloc(sizeof(int));
        int s;
        get_adj(graph, n, u, adj, &s);

        int i;
        for(i=0;i<s;i++)
        {
            int v = adj[i];
            if(color[v] == 0)
            {
                color[v] = 1;
                d[v] = d[u] + 1;
                pi[v] = u;
                enqueue(&Q, v);
                printf("[%d] ~> [%d]\n",u,v);
            }
        }
        color[u] = 2;

    }

}

//BFS :: END -- 


int main(void)
{   
    int graph[MAX][MAX];
    int n = 8;
    create_graph(graph, n);
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 0, 7, 2);
    add_edge(graph, 1, 0, 1);
    add_edge(graph, 1, 6, 1);
    add_edge(graph, 2, 6, 2);
    add_edge(graph, 2, 5, 4);
    add_edge(graph, 2, 3, 3);
    add_edge(graph, 3, 2, 3);
    add_edge(graph, 3, 4, 2);
    add_edge(graph, 4, 3, 2);
    add_edge(graph, 4, 5, 3);
    add_edge(graph, 5, 2, 4);
    add_edge(graph, 5, 4, 3);
    add_edge(graph, 5, 6, 2);
    add_edge(graph, 6, 5, 2);
    add_edge(graph, 6, 2, 2);
    add_edge(graph, 6, 1, 1);
    add_edge(graph, 7, 0, 2);
    print_graph(graph, n);

    BFS(graph, n, 0);
    int p;
    for(p=0;p<n;p++)
        printf("(%d, %d)\t", p, pi[p]);
    printf("\n");

    return 1;
}