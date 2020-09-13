// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

//initialising total words
int words = 0;

//initialising loaded status for dictionary
bool load_dict = false;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //hash the word
    int h = hash(word);

    node *pointer = table[h];
    //check for the word in the linked list
    while (pointer != NULL)
    {
        //if found
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        //else go to next word
        else
        {
            pointer = pointer->next;
        }
    }
    return false;

    //final word in each link
    if (pointer == NULL)
    {
        //if found
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        else
        {
            //if not found return false
            return false;
        }
    }
}


// Hashes word to a number
//source of code http://www.cse.yorku.ca/~oz/hash.html
//djb2
unsigned int hash(const char *word)
{
    unsigned long hash_temp = 5381;
    int c = 0;

    while (c == *word++)
    {
        hash_temp = ((hash_temp << 5) + hash_temp) + c; /* hash * 33 + c */
    }
    return hash_temp % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // open dictionary in read mode
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }



    while (!feof(file))
    {
        char word_dic[LENGTH + 1];

        // read words from file and store word to a new_node
        fscanf(file, "%s", word_dic);

        // increase words count
        words++;

        int h = hash(word_dic);

        //if bucket is empty
        if (table[h] == NULL)
        {
            // allocate space for node
            table[h] = malloc(sizeof(node));

            // check if NULL
            if (table[h] == NULL)
            {
                return false;
            }

            //copy word
            strcpy(table[h]->word, word_dic);

            // pointer in node set to NULL
            table[h]->next = NULL;
        }

        //if bucket is not empty
        else
        {
            // allocate space for new_node
            node *new_node = malloc(sizeof(node));

            // check if NULL
            if (new_node == NULL)
            {
                return false;
            }

            //copy word to the new node
            strcpy(new_node->word, word_dic);

            //switch pointers
            new_node->next = table[h];

            table[h] = new_node;
        }
    }
    // close dictionary
    fclose(file);
    load_dict = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (load_dict)
    {
        return words - 1;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *pointer2 = table[i];
        while (pointer2 != NULL)
        {
            //creates a temp_node and moves to next pointers freeing the previous one
            node *temp_node = pointer2;
            pointer2 = pointer2->next;
            free(temp_node);
            temp_node = NULL;
        }
    }
    //indicates that dictionary is not loaded anymore
    load_dict = false;
    return true;
}
