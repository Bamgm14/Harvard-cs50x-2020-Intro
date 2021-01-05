#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

int main(void)
{
    return true;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(name, candidates[x].name) == 0) //Broteforce check
        {
            for (int y = 0; y < rank; y++)
            {
                if (preferences[voter][y] == x)
                {
                    return false;
                }
            }
            preferences[voter][rank] = x;
            return true;
        }
    }
    return false;
}
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int flag = 0;
    for (int x = 0; x < voter_count; x++)
    {
        flag = 0;
        while (candidates[preferences[x][flag]].eliminated) //Skips all eliminated candidates
        {
            flag += 1;
        }
        candidates[preferences[x][flag]].votes += 1;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int flag = 0;
    string name = "";
    for (int x = 0; x < candidate_count; x++)
    {
        if (voter_count / 2 < candidates[x].votes)
        {
            flag += 1;
            name = candidates[x].name;
        }
    }
    if (flag == 1) //Checks if only one person managed to pass the boundary
    {
        printf("%s\n", name);
        return true;
    }
    else
    {
        return false;
    }
    
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int flag = 1000;
    for (int x = 0; x < candidate_count; x++)
    {
        if (flag > candidates[x].votes && !(candidates[x].eliminated)) //Finds smallest vote tally
        {
            flag = candidates[x].votes;
        }
    }
    return flag;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int flag_1 = 0;
    int flag_2 = 0;
    for (int x = 0; x < candidate_count; x++)
    {
        if (!(candidates[x].eliminated))
        {
            flag_1 += 1;
            if (min == candidates[x].votes)
            {
                flag_2 += 1;
            }
        }
    }
    return flag_1 == flag_2;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    int flag = 0;
    for (int x = 0; x < candidate_count; x++)
    {
        if (min == candidates[x].votes && !(candidates[x].eliminated))
        {
            candidates[x].eliminated = true;
        }
    }
    return;
}
