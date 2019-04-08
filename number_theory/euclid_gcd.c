#include<stdio.h>
#include<stdlib.h>

int euclid(int a, int b)
{
    if(a<b)
    {
        int t = a;
        a = b;
        b = t;
    }
    if(b == 0)
        return a;
    else
    {
        return euclid(b, a%b);
    }
    
}

int main(void)
{
    int i = 10, j = 35;
    printf("GCD %d\n", euclid(i, j));
    return 1;
}