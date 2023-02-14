#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    const int Nmax = 5;
    int N;

    // read-in polynomial degree
    printf("\n Input polynomial degree (0-%i): ", Nmax);
    scanf("%i", &N);
    if (N < 0 || N > Nmax)
    {
        printf(" Invalid value N = %i.\n",N);
        printf(" N must satisfy: 0 <= N <= %i\n\n", Nmax);
        exit(1);
    }
    printf("\n");
    // read-in coefficients
    double b[Nmax+1];
    for (int i=0; i<=N; i++)
    {
        printf(" Set b[%i]: ", i);
        scanf("%lf", &b[i]);
    }
    printf("\n");

    // set x-coordinates
    const int NumPts = 21;
    double x[NumPts];
    for (int i=0; i<NumPts; i++)
    {
        x[i] = -1.0 + i*(2.0/(1.0*(NumPts -1)));
    }
    // Calculate polynomial at x-coordinates
    double y[NumPts];
    //void SamplePoly(const int N,
    //                const int NumPts,
    //                const double b[],
    //                const double x[],
    //                double y[]);
    SamplePoly(N, NumPts, b, x, y);

    // Write to file
    //void WritePoly(const int NumPts,
    //               const double x[],
    //               double y[]);
    WritePoly(NumPts, x, y);

    // Call python script to plot
    system("python3 PlotPoly.py");

    return 0;
}

void SamplePoly(const int N, // polynomial degree
                const int NumPts, // number of x point values
                const double b[], // polynomial coefficients
                const double x[], // x point values
                double y[]) // y(x) output values
{
    for (int i=0; i<NumPts; i++)
    {
        const double a = x[i];
        double phi; y[i] = b[0];
        switch(N)
        {
            case 5:
                phi = 16*pow(a,5) - 20*pow(a,3) + 5*a;
                y[i] += b[5]*phi;
            case 4:
                phi = 8*pow(a,4) - 8*pow(a,2) + 1;
                //phi = 0.125*(105*pow(a,4)-90*pow(a,2)+9);
                y[i] += b[4]*phi;
            case 3:
                phi = 4*pow(a,3) - 3.0*a;
                //phi = 0.5*sqrt(7.0)*(5.0*pow(a,3) -3.0*a);
                y[i] += b[3]*phi;
            case 2:
                phi = 2*pow(a,2)-1;
                //phi = 0.5*sqrt(5.0)*(3.0*pow(a,2) -1.0);
                y[i] += b[2]*phi;
            case 1:
                phi = a;
                //phi = sqrt(3.0)*a;
                y[i] += b[1]*phi;
            case 0:
                phi = 1;
                y[i] += b[0]*phi;
                break;
            default:
                printf("\n Error \n."); exit(1);
        }
    }
}
void WritePoly(const int NumPts,
                const double x[],
                double y[])
{
    FILE *outfile;
    outfile = fopen("poly.data", "w");
    for (int i=0; i<NumPts; i++)
    {
        fprintf(outfile, "%lf %lf \n", x[i], y[i]);
    }
    fclose(outfile);
    return 0;
}
