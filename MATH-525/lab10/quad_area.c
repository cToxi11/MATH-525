#include <stdio.h>
#include "quad.h"
#include <math.h>


void compute_area(quad* qu)
{
    printf("\n I am in the **compute area** function.\n");
    double s = 0;

    s += qu->node1.x * qu->node2.y - qu->node1.y * qu->node2.x;
    s += qu->node2.x * qu->node3.y - qu->node2.y * qu->node3.x;
    s += qu->node3.x * qu->node4.y - qu->node3.y * qu->node4.x;
    s += qu->node4.x * qu->node1.y - qu->node4.y * qu->node1.x;
    qu->area = fabs(s/2);
}
