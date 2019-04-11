//For fully connected component graph (undirected and weighted)
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
    graph[v][u] = w;
    printf("Edge Added %d <~> %d with weight = %d\n", u, v, w);
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
    int value; //Node number
    int weight; //Nodes weight
    struct node *next;
}node;

void enqueue(node **H, int v, int w)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = v;
    new_node->next = NULL;
    new_node->weight = w;
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

int dequeue_min(node **H)
{
    if(*H == NULL)
        return -2;
    else
    {
        int v;
        node *curr = *H;
        node *prev = *H;
        node *p1 = *H;
        node *p2 = *H;
        int M = curr->weight;
        int c = 0;
        while(curr != NULL)
        {
            
            //printf("[%d] (%d) -> ", curr->value, curr->weight);
            if(curr->weight<=M)
            {
                M = curr->weight;
                v = curr->value;
                //printf("\nDEBUG MIN:: M=%d\n", M);
                
                //printf("PREV:: %d, NEXT:: %d\n", prev->weight, curr->weight);

                p1=prev;
                p2=curr;
                
            }
            prev = curr;
            curr = curr->next;

        }
        if(M == (*H)->weight)
        {
            (*H) = (*H)->next;
        }
        else
        {
            p1->next = p2->next;
        }

        return v;
    }   
}

int is_empty(node **H)
{
    if(*H == NULL)
        return True;
    return False;
}

int isPresent(node *H, int v)
{
    if(H == NULL)
        return False;
    else
    {
        node *curr = H;
        while(curr != NULL)
        {
            if(v == curr->value)
                return True;
            else
                curr = curr->next;
        }
        //printf("NULL\n");
    }
    
    return False;
}

void initialize_queue_with_all_vertex(node **H, int (*graph)[MAX], int n)
{
    int u, v;
    for(u=0; u<n; u++)
    {
        for(v=0; v<n; v++)
        {
            if(graph[u][v] != INFINITY && isPresent(*H, v) == False)
            {
                enqueue(&*H, v, graph[u][v]);
            }
        }
    }
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
            printf("[%d] (%d) -> ", curr->value, curr->weight);
            curr = curr->next;
        }
        printf("NULL\n");
            
    }
}

// QUEUE :: END --

int d[MAX];
int pi[MAX];

//DIJKASTRA --BEGIN--



int d[MAX];
int pi[MAX];
 
void mst_prims(int (*graph)[MAX], int n, int s)
{
    int u;
    for(u=0; u<n; u++)
    {
        d[u] = INFINITY;
        pi[u] = -1;
    }
    d[s] = 0;
    node *Q = NULL; 
    enqueue(&Q, s, 0);  //Initializing Q with distance from s is 0
    while(is_empty(&Q) == False)
    {
        u = dequeue_min(&Q);
        int *adj = (int *)malloc(sizeof(int));
        int s_;
        get_adj(graph, n, u, adj, &s_);

        int i;
        for(i=0;i<s_;i++)
        {
            int v = adj[i];
            printf("%d\n", v);
            printf("isPresent = %d and graph[%d][%d] = %d and d[%d] = %d\n", isPresent(Q, v), u, v, graph[u][v], v, d[v]);
            if(graph[u][v] < d[v])
            {
                pi[v] = u;
                d[v] = graph[u][v];
                enqueue(&Q, v, graph[u][v]);
                //see_queue(Q);
            }
            
            
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
        printf("pi[%d] = %d\t", i, pi[i]);
        
        printf("\n");
    }
    
}

void test_Q()
{
    node *Q = NULL;
    enqueue(&Q, 0, 10);
    enqueue(&Q, 1, 80);
    enqueue(&Q, 2, 60);
    enqueue(&Q, 3, 40);
    enqueue(&Q, 4, 20);
    enqueue(&Q, 5, 90);
    printf("%d\n", isPresent(Q, 9));
    
    see_queue(Q);

}

void example()
{
    int n = 9;

    int graph[MAX][MAX];
    create_graph(graph, n);

    add_edge(graph, 0, 1, 4);
    add_edge(graph, 0, 7, 8);
    add_edge(graph, 1, 7, 11);
    add_edge(graph, 1, 2, 8);
    add_edge(graph, 2, 3, 7);
    add_edge(graph, 2, 8, 2);
    add_edge(graph, 2, 5, 4);
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 3, 5, 14);
    add_edge(graph, 4, 5, 10);
    add_edge(graph, 5, 6, 2);
    add_edge(graph, 6, 7, 1);
    add_edge(graph, 6, 8, 6);
    add_edge(graph, 7, 8, 7);

    int *adj = (int *)malloc(sizeof(int));
    int s_;
    get_adj(graph, n, 0, adj, &s_);
    int i;
    for(i=0;i<s_;i++)
        printf("%d\t", adj[i]);
    printf("\n");

    print_graph(graph, n);
    mst_prims(graph, n, 0);
    print_all_param(n);
}

void main(void)
{
    example();
    //test_Q();
}