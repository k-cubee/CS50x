#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // prints the winner if there is one
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    // prints tie if there isn't
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    int value = 0;
    char lower[strlen(word)];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // converts the whole word to lowercase
        lower[i] = tolower(word[i]);
        // adds the points to the variable called value
        if (isalpha(lower[i]))
        {
            value += POINTS[lower[i] - 'a'];
        }
    }
    return value;
}
