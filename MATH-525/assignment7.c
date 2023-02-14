#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nfactorial = 1;
    int i;
    int n;
    printf("Please enter n ");
    scanf("%d", &n);
    if (n < 0)
    {
        printf(" Need a non-negative value! ");
    }
    else
    {
        for (i=1; i<=n; i++)
        {
            nfactorial = nfactorial*i;
        }
        printf(" nfactorial = %i\n", nfactorial );
    }
    return 0;

}








