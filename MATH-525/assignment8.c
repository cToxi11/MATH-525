#include <stdio.h>
int main()
{
    int factorial[10];
    int i;
    // compute some factorials
    factorial[0] = 1;
    for (i=1; i<10; i++)
    {
        factorial[i] = factorial[i-1]*i;
    }
    // output each array element’s value
    for (i=0; i<10; i++)
    {
        printf(" factorial[%i] = %i\n",i,factorial[i]);
    }
    return 0;
}


























