// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 520000;

// Hash table
node *table[N];
int sizevalue = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *possible = table[hash_value];
    while (possible != NULL)
    {
        //printf("%s:%s:",possible->word,word);
        //printf("%i\n",strcasecmp(possible->word,word));
        if (!strcasecmp(possible->word, word))
        {
            return true;
        }
        possible = possible->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hash = 0;
    int n = strlen(word);
    char var[n + 1];
    for (int x = 0; x < n; x++)
    {
        var[x] = tolower(word[x]);
        hash += ((int)var[x] % 97) * (x + 1) * n; // This the best I could come up with
        // I might try to build a new one
    }
    hash += n;
    return hash;
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
    int hashvalue = 0;
    char word[LENGTH + 1];
    char wordredo[LENGTH + 1];
//    while (fgets(word,LENGTH + 1,f)!=NULL) // Press F for fgets
    while (fscanf(f, "%s", word) != EOF) //
    {
        sizevalue += 1;
        /*
        for (int x = 0; x < LENGTH + 1; x++)
        {
            if (word[x] != '\n')
            {
                wordredo[x] = word[x]; //debugger
            }
        }
        */    
        hashvalue = hash(word);
        node *var = malloc(sizeof(node));
        if (var == NULL)
        {
            return false;
        }
        strcpy(var->word, word);
        var->next = table[hashvalue];
        table[hashvalue] = var;
        /*
        while (var!=NULL)
        {
            printf("%s", var->word); //Debugger
            var = var->next;        
        }
        */
    }
    fclose(f);
    return true;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizevalue; // I do nothing
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    
    for (int x = 0; x < N; x++)
    {
        node *var = table[x];
        while (var != NULL)
        {
            node *temp = var;
            var = var->next;
            free(temp); //Memory Is Nice, so let it  be free
        }
    }
    return true;
}
