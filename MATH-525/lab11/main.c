#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main()
{
    // Declare the head node in my list
    node* head = NULL;

    // Set number of letters and generate a new list
    const int num_nodes = GetNumberOfLetters();
    GenerateList(&head, num_nodes);

    // Print list to screen
    Print(1, head); // foward print
    Print(0, head); // reverse print

    // Ask for a key, then search list
    if(num_nodes >0)
    {
        const char key = GetKey();
        SearchList(head,key);
    }
    //const char key = GetKey();
    //SearchList(head,key);
    //Delete list (free up memory)
    DeleteList(&head);
}
