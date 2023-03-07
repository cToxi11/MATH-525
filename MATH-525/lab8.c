#include <stdio.h>
#include <math.h>
int main()
{

    FILE *outfile;
    double x[4];
    double x_exp[4];
    int n;
    printf("Please enter a non-negative integer n ");
    scanf("%d", &n);
    printf("n factorial = %i\n", factorial(n));
    printf("Please enter x array ");
    for (int i=0; i<5; i++)
    {
       double z;
       scanf("%lf", &z);
       x[i] = z;
       x_exp[i] = exp(x[i]);
    }

    printf("exp(x[i]) =  \n");
    for (int i=0; i<5; i++)
    {
       printf("%lf ", x_exp[i]);
    }

    outfile = fopen("output_lab8.data", "w");

    // fprintf(outfile, "n is %i\n", n);
    // fprintf(outfile, "n factorial = %i\n", factorial(n));

    fprintf(outfile, "exp of 0.2 1.2 2.2 3.6 4.6 \n");
    for (int i=0; i<5; i++)
    {
        fprintf(outfile, "%lf ", x_exp[i]);
    }
    fclose(outfile);
    return 0;
}


int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n*factorial(n-1);
    }
}

double exp(double x)
{
    double e = 2.718281828459;
    double ex;
    double z;
    int x0;

    x0 = round(x);
    z = x - x0;
    ex = 0;
    for (int i=0; i<15; i++)
    {
        ex = ex + pow(e,x0)*pow(z,i)/factorial(i);
    }
    return ex;
}























