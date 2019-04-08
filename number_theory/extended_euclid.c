#include<stdio.h>

int extended_euclid(int a, int b, int *x, int *y)
{
    if(a<b)
    {
        int t = a;
        a = b;
        b = t;
    }
    if (b == 0) 
    {
        *x = 1;
        *y = 0;
        return a;
    }
    else
    {
        int x_, y_;
        int d = extended_euclid(b, a%b, &x_, &y_);
        return d;
    }
}

int main(void)
{
    int *x, *y;
    int a = 15, b=10;
    int d = extended_euclid(a, b, x, y);
    printf("%d = %d * %d + %d * %d\n", d, a, *x, b, *y);
}