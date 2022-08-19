#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
// prints a reminder when the user does not cooperate
// and types none or more than one key
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // prints that the key must contain 26 characters if it didn't
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string n_lower_key = "abcdefghijklmnopqrstuvwxyz";
    //creates lower_key and upper_key for lower and upper cases
    char lower_key[25];
    for (int lokey = 0; lokey < 26; lokey++)
    {
        lower_key[lokey] = tolower(argv[1][lokey]);
    }
    char upper_key[25];
    for (int upkey = 0; upkey < 26; upkey++)
    {
        upper_key[upkey] = toupper(argv[1][upkey]);
    }
    for (int argi = 0, n = strlen(argv[1]); argi < n; argi++)
    {
        int check_i = 0;
        // checks whether the key is only alphabets and gives a reminder if it isn't
        if (isalpha(argv[1][argi]) == 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        // checks for duplicate alphabets inside the key and gives a reminder if there is
        for (int kcheck = 0; kcheck < 26; kcheck++)
        {
            if (n_lower_key[argi] != lower_key[kcheck])
            {
                check_i++;
            }
        }
        if (check_i != 25)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    string plaintext = get_string("plaintext:  ");
    int n = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        // returns the original character when it's not an alphabet
        if (isalpha(plaintext[i]) == 0)
        {
            printf("%c", plaintext[i]);
        }
        for (int j = 0; j < 26; j++)
        {
            // ensures that the character stays capitalized
            if (isupper(plaintext[i]) && plaintext[i] - 'A' == j)
            {
                printf("%c", upper_key[j]);
            }
            // ensures that the character stays in lowercase
            else if (islower(plaintext[i]) && plaintext[i] - 'a' == j)
            {
                printf("%c", lower_key[j]);
            }
        }
    }
    printf("\n");
    return 0;
}