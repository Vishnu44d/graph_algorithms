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

void initialize_queue_with_all_vertex(int (*graph)[MAX], int n, node **H)
{
    int i;

}

// QUEUE :: END --
int d[MAX];
int pi[MAX];

//DIJKASTRA --BEGIN--



int d[MAX];
int pi[MAX];
 
void dijkstra(int (*graph)[MAX], int n, int s)
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
            if(d[v] > d[u] + graph[u][v])
            {
                d[v] = d[u] + graph[u][v];
                pi[v] = u;
                enqueue(&Q, v, graph[u][v]);
                printf("[%d] ~> [%d]\n",u,v);
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

void example1()
{
    int n = 5;
    int graph[MAX][MAX];
    create_graph(graph, n);

    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 4, 5);
    add_edge(graph, 1, 2, 1);
    add_edge(graph, 1, 4, 2);
    add_edge(graph, 2, 3, 4);
    add_edge(graph, 3, 2, 6);
    add_edge(graph, 3, 0, 7);
    add_edge(graph, 4, 1, 3);
    add_edge(graph, 4, 2, 9);
    add_edge(graph, 4, 3, 2);

    dijkstra(graph, n, 0);
    print_all_param(n);
}

int main(void)
{
    example1();
    return 1;
}
