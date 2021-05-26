// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int sizenum = 0;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    node *cursor = table[hash(word)];
    while (cursor->next != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char varword[LENGTH];
    strcpy(varword, word);
    for (int i = 0; i < strlen(varword); i++)
    {
        if ((varword[i] >= 'A') && (varword[i] <= 'Z'))
        {
            varword[i] = tolower(varword[i]);
        }
    }
    unsigned int result = 0;
    for (int i = 0, n = strlen(varword); i < n; i++)
    {
        result = (result << 2) ^ varword[i];
    }
    return result % 65536;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    char word[LENGTH];
    for (int i = 0; i < N; i++)
    {
        node *zero = malloc(sizeof(node));
        zero -> next = NULL;
        table[i] = zero;
    }
    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = table[hash(word)];
        table[hash(word)] = n;
        sizenum ++;
        // printf("%s: %i\n",word,hash(word));
    }
    fclose(f);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizenum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

    }
    return true;
}
