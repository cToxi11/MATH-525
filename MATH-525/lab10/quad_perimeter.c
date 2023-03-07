#include <stdio.h>
#include "quad.h"
#include <math.h>


void compute_perimeter(quad* qu)
{
    printf("\n I am in the **compute perimeter** function.\n");
    double s = 0;

    s += sqrt((qu->node1.x-qu->node2.x) * (qu->node1.x-qu->node2.x) + (qu->node1.y-qu->node2.y) * (qu->node1.y-qu->node2.y));
    s += sqrt((qu->node2.x-qu->node3.x) * (qu->node2.x-qu->node3.x) + (qu->node2.y-qu->node3.y) * (qu->node2.y-qu->node3.y));
    s += sqrt((qu->node3.x-qu->node4.x) * (qu->node3.x-qu->node4.x) + (qu->node3.y-qu->node4.y) * (qu->node3.y-qu->node4.y));
    s += sqrt((qu->node4.x-qu->node1.x) * (qu->node4.x-qu->node1.x) + (qu->node4.y-qu->node1.y) * (qu->node4.y-qu->node1.y));

    qu->perimeter = s;
}
