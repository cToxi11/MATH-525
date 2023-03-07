#include <stdio.h>
#include "quad.h"
#include <math.h>

int main()
{
    printf("\n I am in the **main** function.\n");
    quad q;

    printf("Please enter 4 end points' x and y coordinate of the quadrilateral in sequence: \n");
    scanf("%lf %lf", &q.node1.x, &q.node1.y);
    scanf("%lf %lf", &q.node2.x, &q.node2.y);
    scanf("%lf %lf", &q.node3.x, &q.node3.y);
    scanf("%lf %lf", &q.node4.x, &q.node4.y);

    void compute_area(quad* qu);
    compute_area(&q);

    void compute_perimeter(quad* qu);
    compute_perimeter(&q);

    printf("\n I am back to the **main** function.\n");
    printf("\n quadrilateral node #1: ( %12.5e, %12.5e )", q.node1.x, q.node1.y);
    printf("\n quadrilateral node #2: ( %12.5e, %12.5e )", q.node2.x, q.node2.y);
    printf("\n quadrilateral node #3: ( %12.5e, %12.5e )", q.node3.x, q.node3.y);
    printf("\n quadrilateral node #4: ( %12.5e, %12.5e )", q.node4.x, q.node4.y);
    printf("\n area = %12.5e\n\n", q.area);
    printf("\n perimeter = %12.5e\n\n", q.perimeter);
}










