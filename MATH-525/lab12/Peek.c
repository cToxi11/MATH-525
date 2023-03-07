#include "node.h"
#include "string.h"

void Peek(node *top, char *name)
{
    strcpy(name, top->name);
}
