// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
//static const unsigned int N = 26;
#define N 26
// Hash table
node *table[N];

// Count of words
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    for (int i = 'A'; i <= 'Z'; i++){
        if(toupper(word[0]) == i){
            return (i - 'A');
        }
    }

    // ASCII value of A=65 and Z=90
    // for (int i = 65; i <= 90; i++){
    //     // Integer i with %c will be converted to character
    //     if(toupper(word[0]) == i){
    //         return (i - 'A');
    //     }
    // }

    return -1;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

/*
Open the dictionary file and load the data in to the hash-table
return true or false.

Take a word as inpit.
Output the index of which bucket the word belongs to
At each of the array index there should be a linked list, (Hash table: array of linked lists)
To determine which of those linked list you insert a word in-to is based on the hash function
(take a strin or a word as input, output is a nuber that's generated from that input
corresponding to which of the linked list, to place this particular word in to)

Steps for the load function
1. Open the dictionary file.
file = fopen();

2. Read the strings from the file one at a time.
fscanf(file, "%s", word); // untill you reach the end of the file.

3. Create new node for each word.
//To allocate memory for the node defined as a structure
node *n = malloc(sizeof(node));
//To put a word in to the structure of the node.
strcpy(n->word, "Hello");
//To set the next node to null, "n" is the addrerss of the node.
n->next = NULL;

4. Hash word to obtain a hash value.
Use the "Hash" function to determine which index linked list the word belings to inside the hash table.

5. Index into the hash table to determine which of those linked lists to use inside the hash table
when inserting this node into a linked list.
 - Add a new node to the linked list.
*/
    // TODO
    FILE* dictionary_file = fopen("/mnt/c/Minindu/cs50/cs50_local/speller/dictionaries/small", "r");

    if (!dictionary_file){
        printf("Failed to open the file.\n");
        return 1;
    }
    char* word = malloc((LENGTH + 1) * sizeof(char));
    //char word[LENGTH +1];
    if (word == NULL){
        printf("Failed to allocate Memory for word.\n");
        return 1;
    }
    while(fscanf(dictionary_file, "%s", word) == 1){
        printf("%s\n", word);
        num_words++;
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n -> next = NULL;

        int index = hash(word);
        if (index){
        (n -> next) = (table[index]); //table[index] is pointer to a node ,Address of table[index] assigned to n-> next
        table[index] = n;
        }else{
            return 1;
        }
    };
    //printf("%i\n", num_words);
    //free(word);
    fclose(dictionary_file);

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
