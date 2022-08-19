#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Asks the user for the text
    string text = get_string("Text: ");
    // Initialzes letter_count, word_count and sentence_count
    float letter_count = 0;
    float word_count = 0;
    float sentence_count = 0;
    // Goes through the text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // If text[i] is an alphabet, then increment letter_count by 1
        if (isalpha(text[i]))
        {
            letter_count++;
        }
        // If text[i] is an a space, then increment word_count by 1
        if (text[i] == ' ')
        {
            word_count++;
        }
        // If text[i] is not an alphabet and a space follows it, add 1 to sentence_count
        if (text[i + 1] == ' ' && (text[i] == '.' || text[i] == '!' || text[i] == '?'))
        {
            sentence_count++;
        }
        // If the end of the text is reached, add word_count and sentence_count by 1
        if (i == n - 1 && isalpha(text[n - 2]) && text[n - 1] != '"')
        {
            word_count++;
            sentence_count++;
        }
    }
    // If the final letter is an double quote, then increment word_count by 1
    if (text[strlen(text) - 1] == '"')
    {
        sentence_count++;
        word_count++;
    }
    // Calculates how many letters there are per 100 words
    float L = (letter_count / word_count) * 100;
    // Calculates how many sentences there are per 100 words
    float S = (sentence_count / word_count) * 100;
    // Calculates the index according to the formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int rounded_index = round(index);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", rounded_index);
    }
}