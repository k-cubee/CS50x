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

// N = Max size of the sum of word with 45 uppercase "Z" + 2 more "Z"'s
const unsigned int N = 'Z' *(LENGTH + 2);


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
    // Hashes according to the sum of the chars in the word
    int sum_word = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum_word += toupper(word[i]);
    }
    // Adds the first char for more variablilty
    sum_word += toupper(word[0]);
    int r = sum_word % strlen(word);
    // Also adds the char at the index = to the remainder of total sum divided by word length
    sum_word += toupper(word[r]);
    return sum_word;
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
