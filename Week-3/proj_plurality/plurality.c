#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAX 9

int main(void)
{
    return true;
}

typedef struct
{
    string name;
    int votes;
}
candidate;

int candidate_count;
candidate candidates[MAX];

bool vote(string name) 
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(name, candidates[x].name) == 0) //Broteforce check 
        {
            candidates[x].votes += 1;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int f = 0;
    for (int x = 0; x < candidate_count; x++)
    {
//        printf("%d %d %d\n",f ,name_list[x].vote, f < name_list[x].vote); //Debugger
        if (f < candidates[x].votes) // Finds highest
        {
            f = candidates[x].votes; 
        }
//        printf("%d\n", f); //Debugger
    }
    for (int x = 0; x < candidate_count; x++)
    {
//        printf("Equal:%d\nVote:%d\nFlag:%d\n",f == name_list[x].vote, name_list[x].vote, f); //Debugger
        if (f == candidates[x].votes) // Prints all of the highest value
        {
            printf("%s\n", candidates[x].name);
        }
    }
    return;
}
