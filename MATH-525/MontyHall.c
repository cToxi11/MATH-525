#include <stdio.h>
int main()
{
    // Where is the grand prize?
    srand(time(NULL));
    int prize = rand()%3; // 0 <= rand() <= 32767
    int notprize1 = (prize + 1)%3;
    int notprize2 = (prize + 2)%3;

    // Ask contestant to pick a door
    printf("\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(" ** Monty Hall Simulator **\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("\n");
    int pick = -1;
    while(pick < 0 || pick > 2)
    {
        printf(" Pick a door (0, 1, or 2): ");
        scanf("%d", &pick);
    }

    printf("\n You entered: %d\n", pick);

    // Tell contestant about another door
    int other;
    int other_other;
    printf("\n Interesting choice ...\n");
    if (pick == prize)
    {
        int ss = rand()%2;
        if (ss==0)
        {
            other = notprize1;
            other_other = notprize2;
        }
        else
        {
            other = notprize2;
            other_other = notprize1;
        }
    }
    else
    {
        other_other = prize;
        if (pick==notprize1)
        {
            other = notprize2;
        }
        else
        {
            other = notprize1;
        }
    }
    printf("\n I can tell you for sure that the prize is not behind door: %i\n",other);

    // Ask if they want to change
    int change = -1;
    while(change != 0 && change != 1)
    {
        printf("\n Stay with Door %i (press 0) or switch to Door %i (press 1): ", pick,other_other);
        scanf("%d", &change);
    }
    int final_pick;
    if (change == 0)
    {
        final_pick = pick;
        printf("\n You stayed with Door %i\n ",final_pick);
    }
    else
    {
        final_pick = other_other;
        printf("\n You switched to Door %i\n ",final_pick);
    }
    // Check answer
    if (final_pick == prize)
    {
        printf("\n *** WINNER ***\n\n");
    }
    else
    {
        printf("\n --- LOSER ---\n\n");
    }
    printf(" The prize was behind Door %i\n\n",prize);

    return 0;
}
























