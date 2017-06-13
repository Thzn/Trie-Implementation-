#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26


typedef enum { TRUE, FALSE } boolean;

typedef struct TrieNode{
    struct TrieNode *children; 
    char label;
    boolean isEndOfWord;
} TrieNode;


TrieNode* createNode();
TrieNode* search(TrieNode *root,char* substring);
void traverse(char* prifix,TrieNode* root);
void insert(TrieNode *root,char *word);
