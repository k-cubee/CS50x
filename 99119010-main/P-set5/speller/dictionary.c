// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Global variable for size function
unsigned int check_num = 0;

// N = Max size of base-26 with three numbers
const unsigned int N = 19683;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hashes the word
    int hash_no = hash(word);
    // Transverses through the hash table and its linked lists until NULL is reached
    for (node *i = table[hash_no]; i != NULL; i = i->next)
    {
        if (strcasecmp(i->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes according to the first three letters
unsigned int hash(const char *word)
{
    // Initializes return value
    int total;
    // Considers the case where the word is just one letter
    if (strlen(word) == 1)
    {
        if (word[0] != '\'')
        {
            total = toupper(word[0]) - 'A';
        }
        else
        {
            total = 26;
        }
    }
    // Considers the case where the word is just two letters
    else if (strlen(word) == 2)
    {
        int word0, word1;
        if (word[0] != '\'')
        {
            word0 = (toupper(word[0]) - 'A') * 27;
        }
        else
        {
            word0 = 26 * 27;
        }
        if (word[1] != '\'')
        {
            word1 = toupper(word[0]) - 'A';
        }
        else
        {
            word1 = 26;
        }
        total = word0 + word1;
    }
    else
    {
        int word0, word1, word2;
        if (word[0] != '\'')
        {
            word0 = (toupper(word[0]) - 'A') * 27 * 27;
        }
        else
        {
            word0 = 26 * 27 * 27;
        }
        if (word[1] != '\'')
        {
            word1 = (toupper(word[0]) - 'A') * 27;
        }
        else
        {
            word1 = 26 * 27;
        }
        if (word[2] != '\'')
        {
            word2 = toupper(word[0]) - 'A';
        }
        else
        {
            word2 = 26;
        }
        total = word0 + word1 + word2;
    }
    return total;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    // Reads each word from the file until the end of file is reached
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Assigns the word to the first place of the hash table
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, word);
        unsigned int hash_no = hash(word);
        temp->next = table[hash_no];
        table[hash_no] = temp;
        // Keeps track of the amount of words counted
        check_num++;
    }
    // Closes file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returns the amount of words in the dictionary from the global variable check_num
    if (check_num != 0)
    {
        return check_num;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Frees each element in linked list
    for (int i = 0; i < N; i++)
    {
        node *temp = NULL;
        while (table[i] != NULL)
        {
            temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
        if (i == N - 1)
        {
            return true;
        }
    }
    return false;
}
