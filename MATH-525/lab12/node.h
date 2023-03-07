#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node;
struct node  // define a node structure for Stack example with famous warplanes
{
    int position; // node position
    char name[100]; // plane name
    char country[100]; // country
    int year; // Service year

    node* next;
};

void DisplayStack(node* top);
void ExecuteOption(const int option, node** top);
void Push(const char *name, const char *country, const int year, node** top);
void Pop(node** top, char *output);
void Peek(node *top, char *name);
void GetStackSize(node* top, int* stack_size);
void DisplayStack(node* top);
void PrintNode(node* top);
#endif














