#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    /* data */
    int rank;
    int value;
    struct node *parent;
}node;

void makeset(node *n, int value)
{
    n->rank = 0;
    n->parent = NULL;
    n->value = value;
    printf("DISJOINT SET created with a value %d and rank %d\n", n->value, n->rank);
}

int findset(node *n)
{
    if(n->parent == NULL)
        return n->rank;
    else
    {
        node *curr = n;
        while(curr->parent != NULL)
            curr = curr->parent;
        return curr->rank;
    }
    
}

node *union_set(node *n1, node *n2)
{
    node *new_parent = (node *)malloc(sizeof(node));
    int r1, r2;
    r1 = findset(n1);
    r2 = findset(n2);
    printf("RANKs are %d, %d\n", r1, r2);
    if(r1>r2)
    {
        n2->parent = n1;
        n1->rank += 1;
        new_parent = n1;
        printf("DEBUG IF:: %d union %d(parent)\n", n2->rank, n1->rank);
        printf("IF:: RANK OF NEW PARENT %d\n", new_parent->rank);
    }
    else
    {
        n1->parent = n2;
        n2->rank += 1;
        new_parent = n2;
        printf("DEBUG ELSE:: %d union %d(parent)\n", n1->rank, n2->rank);
        printf("ELSE:: RANK OF NEW PARENT %d\n", new_parent->rank);
    }
    return new_parent;
}

void print_tree()
{

}

int main(void)
{
    node *n1 = (node *)malloc(sizeof(node));
    node *n2 = (node *)malloc(sizeof(node));
    node *n3 = (node *)malloc(sizeof(node));
    node *n4 = (node *)malloc(sizeof(node));
    node *n5 = (node *)malloc(sizeof(node));
    node *np = (node *)malloc(sizeof(node));
    makeset(n1, 2);
    makeset(n2, 4);
    makeset(n4, 8);
    makeset(n3, 10);
    makeset(n5, 20);

    np = union_set(n1, n2);
    np = union_set(n4, n3);
    np = union_set(n4, n5);
    np = union_set(n1, n5);
    printf("FIND SET:: %d\n", findset(n1));
    return 1;
}