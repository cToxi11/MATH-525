#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "string.h"

void Push(const char *name, const char *country, const int year, node** top)
{
    // Add a node from head (create one if the stack is empty)
    if (*top == NULL)
    {
        *top =(node*)malloc(sizeof(struct node));
        (*top)->next = NULL;
        (*top)->year = year;
        strcpy((*top)->name, name);
        strcpy((*top)->country, country);
        (*top)->position = 1;
    }
    else
    {
        node* temp;
        temp =(node*)malloc(sizeof(struct node));
        temp->next = *top;
        temp->year = year;
        strcpy(temp->name, name);
        strcpy(temp->country, country);
        temp->position = 1;
        *top = temp;
        node* ptr = (*top)->next;
        while (ptr!=NULL)
        {
            ptr->position = ptr->position+1;
            ptr = ptr->next;
        }
    }
}






