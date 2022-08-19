#include <cs50.h>
#include <stdio.h>
#include <string.h>

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

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // iterates through the array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the name of the candidate is the same as the j'th rank of i'th voter, will set the index of it
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    for (int i = 0; i < voter_count; i++)
    {
        int ranking = 0;
        // if first preference or the preferences that come later have been eliminated, will ignore those
        for (int k = 0; candidates[preferences[i][k]].eliminated == true; k++)
        {
            ranking++;
        }
        // if the preference has not been eliminated and is the top preference, increments the vote of the candidate by 1
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(candidates[j].name, candidates[preferences[i][ranking]].name) == 0)
            {
                candidates[j].votes++;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // looks for a candidate with more than half the votes and prints their name
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // sets the lowest number of votes to the first candidate's
    int lowest = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++)
    {
        // if lowest is less than the next candidate's number of votes, the lowest will change to their's
        if (lowest > candidates[i].votes && candidates[i].eliminated == false)
        {
            lowest = candidates[i].votes;
        }
    }
    return lowest;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // initialized variables i_tie and leftover
    int i_tie = 0;
    int leftover = candidate_count;
    for (int i = 0; i < candidate_count; i++)
    {
        // checks how many candidates has been eliminated and decrements the total number of candidates
        if (candidates[i].eliminated)
        {
            leftover--;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // increments i_tie by 1 when a candidate has the lowest number of votes
        if (min == candidates[i].votes && candidates[i].eliminated == false)
        {
            i_tie++;
            // checks whether everyone leftover got the lowest number of votes
            if (i_tie == leftover)
            {
                return true;
            }
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // eliminates the candidate with the lowest number of vote if there is no tie
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}