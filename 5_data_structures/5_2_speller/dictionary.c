// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
// Helper hash value
unsigned int hash_value;
// Helper word count
int words = 0;

void freespace(node *n);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find which index the word should be indexed at
    hash_value = hash(word);
    // Check if first occurence is the word
    if (strcasecmp(word, table[hash_value] -> word) == 0) {
        return true;
    }
    // Set tmp to next occurence
    node *tmp = table[hash_value] -> next;
    // While tmp is not null search for the word in bucket
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp -> word) == 0) {
            return true;
        }
        // Set temp to be next value within current index
        tmp = tmp -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function that takes the first 2 letters and hashes to a index in the hash table
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *buffer = fopen(dictionary, "r");
    if (buffer != NULL)
    {
        // Prepare to load dictionary with auxiliary variables
        // Index of the curr word
        int index = 0;
        // Word variable to be mounted from char sequence
        char w[LENGTH + 1];
        // Current char in stream
        char c;
        // While reading the file
        while (fread(&c, sizeof(char), 1, buffer))
        {
            // If char is not EOL add char to current word and proceed to next index
            if (c != 10)
            {
                w[index] = c;
                index++;
            }
            // If char is EOL add current word to the hash adding \0 to the last index table and reset aux variables
            else if (c == 10)
            {
                // Format word to be recognized as a string correctly with \0
                w[index] = '\0';
                // Run hashing function to get bucket
                hash_value = hash(w);
                // Update words count
                words++;
                // Move index back to 0
                index = 0;
                // Save word to memory allocating memory for a root node if it's nil or going until last node in bucket
                // If current node still doesn't exist allocate memory for it and create word
                if (table[hash_value] == NULL) {
                    table[hash_value] = malloc(sizeof(node));
                    // Handle malloc error
                    if (table[hash_value] == NULL) {
                        printf("Memory allocation error");
                        return false;
                    }
                    // Copy string to string slot
                    strcpy(table[hash_value] -> word, w);
                    // Set next to NULL as its the root node
                    table[hash_value] -> next = NULL;
                }
                // If current node already exists iterate until next is null and create new node
                else
                {
                    // Get current node, root at first
                    node *curr = table[hash_value];
                    // Iterate and update curr until end is reached
                    while (curr -> next != NULL)
                    {
                        curr = curr -> next;
                    }
                    // Allocate memory for the new ndoe
                    node *tmp = malloc(sizeof(node));
                    // Handle memory allocation error
                    if (tmp == NULL) {
                        printf("Memory allocation error");
                        return false;
                    }
                    // Copy word to word slot in tmp
                    strcpy(tmp -> word, w);
                    // Set next to NULL
                    tmp -> next = NULL;
                    // Set curr next to tmp
                    curr -> next = tmp;
                }
            }
        }
        // Close dictionary
        fclose(buffer);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Recursive function that will go until the base case of each bucket index and free space
    for (int i = 0; i < 26; i++)
    {
        freespace(table[i]);
    }
    return true;
}

void freespace(node *n)
{
    if (n -> next == NULL) {
        free(n);
        return;
    }
    freespace(n -> next);
    free(n);
    return;
}
