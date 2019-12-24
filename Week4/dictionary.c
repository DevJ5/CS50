// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node structure for this word
        node *newNodePtr = malloc(sizeof(node));
        if (newNodePtr == NULL)
        {
            printf("Error: Not enough memory");
            return 1;
        }
        // Set the word and the next properties
        strcpy(newNodePtr->word, word);
        newNodePtr->next = NULL;
        // Hash the word
        int key = hash(word);

        if (hashtable[key] != NULL)
        {
            newNodePtr->next = hashtable[key];
        }
        hashtable[key] = newNodePtr;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            node *currentNodePtr = hashtable[i];
            count++;

            while (currentNodePtr->next != NULL)
            {
                count++;
                currentNodePtr = currentNodePtr->next;
            }
        }
    }
    return count = 0 ? 0 : count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Word should be in lowercase
    char wordcpy[LENGTH + 1];
    strcpy(wordcpy, word);

    for (int i = 0; wordcpy[i]; i++)
    {
        wordcpy[i] = tolower(wordcpy[i]);
    }
    // Get hash
    int key = hash(wordcpy);
    if (hashtable[key] != NULL)
    {
        node *currentNodePtr = hashtable[key];
        while (true)
        {
            if (strcmp(currentNodePtr->word, wordcpy) == 0)
            {
                // Word is found, return true
                return true;
            }
            if (currentNodePtr->next == NULL)
            {
                // We are at the last node, break
                break;
            }
            // Set the currentNode to the next node and start loop again
            currentNodePtr = currentNodePtr->next;
        }
    }

    // Word isn't found, return false
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            node *currentNodePtr = hashtable[i];
            while (currentNodePtr->next != NULL)
            {
                node *temp = currentNodePtr;
                currentNodePtr = currentNodePtr->next;
                free(temp);
            }
            free(currentNodePtr);
        }
    }

    return true;
}
