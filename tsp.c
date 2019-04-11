#include<stdio.h>
#include<stdlib.h>

#define MAX 20
#define WHITE 0
#define GRAY 1
#define BLACK 2


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
    printf("Graph created of %d vertex.\n", i);
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
    printf("\nEdge added %d ~> %d.", u, v);
    //add_edge(&*graph, v, u);   
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
    color[u] = GRAY;
    t = t + 1;
    d[u] = t;
    if(graph[u] != NULL)
    {
        nodes *curr = graph[u];
        while(curr != NULL)
        {
            int v = curr->val;
            if(color[v] == WHITE)
            {
                pi[v] = u;
                printf("[%d] ~> [%d]\n", u, v);
                dfs_visit(&*graph, v);
            }
            curr = curr -> next;
        }
        color[u] = BLACK;
        t = t + 1;
        f[u] = t;

    }
}

void dfs(nodes *graph[], int n)
{
    int u;
    for(u=0;u<n;u++)
    {
        color[u] = WHITE;
        pi[u] = -1;
    }
    t = 0;
    for(u=0;u<n;u++)
    {
        if(color[u] == WHITE)
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

    print_graph(&*graph, n);
        
    dfs(&*graph, n);
    print_all_param(n);

    return 1;
}