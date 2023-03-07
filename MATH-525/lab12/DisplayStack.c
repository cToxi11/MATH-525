#include <stdio.h>
#include <stdlib.h>
#include "node.h"
void DisplayStack(node* top)
{
    //Print the Stack
    if (top==NULL)
    { printf(" Stack is emtpy.\n"); return; }

    printf(" -----------------------------------------------------------------------------------\n");
    printf(" |Pos:| Name:  | Country: | Service Year: | Address: | Next: |\n");
    printf(" -----------------------------------------------------------------------------------\n");
    PrintNode(top);
    printf(" -----------------------------------------------------------------------------------\n");
}

void PrintNode(node* top)
{
    printf(" |%3i |%7s |%6s |%10i| %15p |%15p |\n", top->position ,top->name,top->country,top->year,top,top->next);
    if (top->next == NULL)
    { return; }
    PrintNode(top->next);
}
