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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// number of words loaded in dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // find the bucket this word belongs to
    unsigned int index = hash(word);

    // start at first node in that bucket
    node *cursor = table[index];

    // loop through the list
    while(cursor !=NULL){
        // compare words ignoring upper or lowercase
        if(strcasecmp(cursor->word, word) == 0){
            return true;
        }
        // move to next node
        cursor = cursor->next;
    }
    // reaches end of list or word doesnt exist
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // start with hash vlue 0
    unsigned int hash = 0;

    // loop over the characters
    for (int i = 0; word[i]!='\0'; i++){
        // convert to lower case to produce the same hash
        char c = tolower(word[i]);
        //multiply previous value by 31 and add ASCII value of current char
        hash = hash * 31 + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary in read mode
    FILE *file = fopen(dictionary, "r");

    // if failed, return false
    if(file == NULL){
        return false;
    }
    // buffer to temporarily store one word
    char word[LENGTH + 1];

    // read one word at a time until EOF
    while(fscanf(file, "%45s", word) != EOF){
        node *new_node = malloc(sizeof(node));

        // if failed
        if(new_node == NULL){
            fclose(file);
            return false;
        }
        // copy the word in the node
        strcpy(new_node->word, word);

        // hash word to decide which bucket to put into
        unsigned int index = hash(word);

        // Insert node at the beginning of the linked list.
        new_node->next = table[index];
        table[index] = new_node;

        // increase dictionary size;
        word_count++;
    }
    // close dictionary
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // go through every bucket
    for(int i = 0; i < N; i++){
        // start at head
        node *cursor = table[i];

        // iterate through list
        while(cursor != NULL){
            // save next node before freezing current
            node *temp = cursor;

            // move cursor forward
            cursor = cursor->next;

            // free old one
            free(temp);
        }
    }
    return true;
}
