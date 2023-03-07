#include <stdlib.h>
#include "node.h"
// Main Function
int main()
{
    node* top = NULL;

    int option=0;
    while(option!=6)
    {
        ExecuteOption(option ,&top); // Call Function to act with the option value
        option = QueryOption(); // Call Function to input the option
    }

    DeleteStack(&top); //delete the record and free the memory
    return 0;
}
