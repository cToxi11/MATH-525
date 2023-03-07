#include <stdlib.h>
#include "node.h"
#include "string.h"
#include <stdio.h>
// pop the top node from stack

void Pop(node** top, char *output)
{
    node* temp = *top;

    if (temp==NULL)
    { return; }
    else
    { temp = temp->next; }

    strcpy(output, (*top)->name);

    free(*top);
    *top = temp;


    node* ptr = *top;
    while (ptr!=NULL)
    {
        ptr->position = ptr->position -1;
         ptr = ptr->next;
    }
}
