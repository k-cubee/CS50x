#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool check_loop(int winner, int loser);

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
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Compares each candidate to the input name and adds them to the ranks array and returns true
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If the input name does not match any of the candidates' then return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Ensures that i and j is different
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Since i is always ranked higher than j, add increments preferences[ranks[i]][ranks[j]] by 1
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Goes over every pair and if preferences[i][j] is greater than preferences[j][i], i wins and j loses
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // If preferences[i][j] is not tied, then increases the pair_count by 1
                if (!(preferences[i][j] == preferences[j][i]))
                {
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort algorithm
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Initializes swap
        int swap = 0;
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            // If the first pair's strength  has less votes than the one next to it, then swap the pairs and adds 1 to swap
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
                swap++;
            }
        }
        // If no swaps occur, then the sort is complete
        if (swap == 0)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Calls the function check_loop and checks whether it returns true or false
        if (check_loop(pairs[i].winner, pairs[i].loser) == false)
        {
            // If it returns false then add the edge
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Initializes contains_true
        bool contains_true = false;
        for (int j = 0; j < candidate_count; j++)
        {
            // Checks for each candidate on whether they have an edge towards them
            if (locked[j][i] == true)
            {
                // If they do, then change contains_true to true
                contains_true = true;
            }
        }
        // If contains_true is still false by the end of every check, then print the winner
        if (contains_true == false)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

bool check_loop(int winner, int loser)
{
    // Initializes check and loser_list array
    int check = 0;
    int loser_list[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks whether the loser has any edge over someone
        if (locked[loser][i] == true)
        {
            // If they do, add the loser of the loser's edge to the loser_list and increment check by 1
            loser_list[check] = i;
            check++;
        }
    }
    // If the loser doesn't have any edge away from them, then return false (add the edge)
    if (check == 0)
    {
        return false;
    }
    else
    {
        // If the loser have an edge to someone then check whether the loser of loser's have an edge towards the winner
        for (int i = 0; i < check; i++)
        {
            if (locked[loser_list[i]][winner])
            {
                // If they do, then return true (don't add the edge)
                return true;
            }
            else
            {
                // If the loser's loser does not have an edge to the winner, then call the function again with the
                // loser of the loser as the loser
                if (check_loop(winner, loser_list[i]))
                {
                    return true;
                }
            }
        }
    }
    return false;
}