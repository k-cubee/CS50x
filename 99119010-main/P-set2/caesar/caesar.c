#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
// prints a reminder when the user does not cooperate
// and types none or more than one key
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // prints a reminder when the user types non-positive/non-integers
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // converts the argv string to an int
    int key = atoi(argv[1]);
    // ensures that the key is between 0-25
    key = key % 26;
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int j = 0, n = strlen(plaintext); j < n; j++)
    {
        // returns the original character when it's not an alphabet
        if (isalpha(plaintext[j]) == 0)
        {
            printf("%c", plaintext[j]);
        }
        int overflow = plaintext[j] + key;
        if (islower(plaintext[j]) && overflow <= 'z')
        {
            char newtext = plaintext[j] + key;
            printf("%c", newtext);
        }
        // ensures that the alphabet stays as alphabet
        else if (islower(plaintext[j]))
        {
            int left_over = overflow - 'z';
            char newtext = 'a' + left_over - 1;
            printf("%c", newtext);

        }
        if (isupper(plaintext[j]) && overflow <= 'Z')
        {
            char newtext = plaintext[j] + key;
            printf("%c", newtext);
        }
        // ensures that the alphabet stays as alphabet
        else if (isupper(plaintext[j]))
        {
            int left_over = overflow - 'Z';
            char newtext = 'A' + left_over - 1;
            printf("%c", newtext);
        }
    }
    printf("\n");
    return 0;
}