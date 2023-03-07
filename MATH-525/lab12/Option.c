#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int QueryOption()
{
    int option;
    printf(" ENTER CHOICE : ");
    scanf("%i", &option);
    return option;
}

void ExecuteOption(const int option, node** top)
{
    int year;
    char input_name[100];
    char input_county[100];
    int value;
    switch(option)
    {
        case 0: // Display available options
            DisplayOptions();
            break;
        case 1: // Enter a new record then push new node to stack
            printf(" Enter plane name : ");
            scanf("%s", input_name);
            printf(" Enter county: ");
            scanf("%s", input_county);
            printf(" Enter service year: ");
            scanf("%i", &year);
            Push(&input_name, &input_county, year, top);
            break;
        case 2: // Pop top node off of stack, display the plane name
            if (*top!=NULL)
            {
                char plane_name[100];
                Pop(top, plane_name);
                printf(" Pop plane = %s\n",plane_name);
            }
            else
            { printf(" Stack is empty.\n"); }
            break;
        case 3: // Peek at top plane on stack
            if((*top)!=NULL)
            {
                char plane_name[100];
                Peek(*top, plane_name);
                printf(" Top plane is %s\n", plane_name);
            }
            else
            { printf(" Stack is empty.\n"); }
            break;
        case 4: // Display the entire stack
            DisplayStack(*top);
            break;
        case 5: // Print stack size
            GetStackSize(*top,&value);
            printf(" Stack size is %i\n",value);
            break;
        case 6: // Do nothing here, but this causes code to end
            break;
        default:
            printf("Error: incorrect option. Try again.\n");
            break;
    }
}
