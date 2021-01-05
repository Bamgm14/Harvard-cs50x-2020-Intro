#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
        //printf("%s\n",candidates[i]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    add_pairs();
    /*    
        for (int x = 0; x < candidate_count; x++)
        {
            for (int y = 0; y < candidate_count; y++)
                {
                    printf("|%i|",preferences[x][y]);
                }
            printf("\n");
        }
    */
//    printf("%i\n",pair_count);
    sort_pairs();
    /*
        for (int x = 0; x < pair_count; x++)
        {
            printf("Loser:%i\nWinner:%i\n",pairs[x].loser,pairs[x].winner);
        }
    */
    lock_pairs();
    /*
        for (int x = 0; x < candidate_count; x++)
        {
            for (int y = 0; y < candidate_count; y++)
            {
                printf("|%i|",locked[x][y]);
            }
        printf("\n");
        }
    */
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(candidates[x], name) == 0)
        {
            ranks[rank] = x;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = x + 1; y < candidate_count; y++)
        {
            preferences[ranks[x]][ranks[y]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = x + 1; y < candidate_count; y++)
        {
            if (preferences[x][y] != preferences[y][x])
            {
                pairs[pair_count].winner = x * (bool)((preferences[x][y] + 1) / (preferences[y][x] + 1)) + y * (bool)((preferences[y][x] + 1) / 
                                           (preferences[x][y] + 1));
                pairs[pair_count].loser = y * (bool)((preferences[x][y] + 1) / (preferences[y][x] + 1)) + x * (bool)((preferences[y][x] + 1) / 
                                          (preferences[x][y] + 1));
                pair_count++;
            }
        }
    }
    return;
}
//Sorting Requests.
int sort(const void *a, const void *b)
{
    pair *c = (pair *)a;
    pair *d = (pair *)b;
    return (preferences[d->winner][d->loser] - preferences[c->winner][c->loser]);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    qsort(pairs, pair_count, sizeof(pair), sort);
    return;
}
bool repeater(int i, bool visited[])
{
    if (visited[i])
    {
        return true;
    }
    visited[i] = true;
    for (int x = 0; x < candidate_count; x++)
    {
        if ((locked[i][x]) && (repeater(x, visited)))
        {
            return true;
        }
    }
    return false;
}
bool cycle(int begin)
{
    bool visited[candidate_count];
    for (int x = 0; x < candidate_count; x++)
    {
        visited[x] = false;
    }
    //return false;
    return !(repeater(begin, visited));
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int x = 0; x < pair_count; x++)
    {
        locked[pairs[x].winner][pairs[x].loser] = true;
        locked[pairs[x].winner][pairs[x].loser] = cycle(pairs[x].winner);
    }
    return;
}

bool is_source(int i)
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (locked[x][i])
        {
            return false;
        }
    }
    return true;
}
int *get_source(int *sum)
{
    for (int x = 0; x < candidate_count; x++)
    {
        sum[x] = false;
    }
    for (int x = 0; x < candidate_count; x++)
    {
        sum[x] = is_source(x);
        //printf("%i\n",sum[x]);
    }
    return sum;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    //printf("Candidate:%i\nSum:%i\n",candidate_count,sum);
    
    //printf("\n");
    int input[candidate_count];
    int *sum = get_source(input);
    for (int x = 0; x < candidate_count; x++)
    {
        //printf("%i\n",sum[x]);
        if (sum[x])
        {
            printf("%s\n", candidates[x]);
        }
    }
    return;
}