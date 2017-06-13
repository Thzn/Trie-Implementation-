#include <stdio.h>
#include <stdlib.h>
#include "AutoCompleteImpl.h"


#define NUMBER_OF_WORDS (354935)
#define INPUT_WORD_SIZE 100


char *receiveInput(char *s) {
    scanf("%99s", s);
    return s;
}
boolean validate(char*  word){
	int i=0;	
	for(;i<strlen(word); i++){
		if(!(word[i] <= 122 && word[i] >= 97)){   
		return FALSE;
		} 
	}
return TRUE;
}
int main(){
    int i;
    TrieNode* root;
    root=createNode();
    root->isEndOfWord=FALSE;
    root->label='#';
    
    FILE *fp = fopen("resources/dictionary.txt", "r");
    if (fp == NULL){
        fprintf(stderr, "Error while opening dictionary file");
        exit(1);
    }
    
    //Read through the file insert each word to Trie
    char* word=(char*)malloc(sizeof(INPUT_WORD_SIZE)*sizeof(char));
    for(i=0;i<NUMBER_OF_WORDS;i++){
        fscanf(fp,"%s",word);
        insert(root,word);    
    }

    while (1) {
        printf("Enter keyword: ");
        char str[100];
        receiveInput(str);
        printf("\n==========================================================\n");
        printf("\n********************* Possible Words ********************\n");
        if(validate(str) == TRUE){ //Check the input String
			traverse(str,root);
        }else{
		   printf("WRONG INPUT\n");	
		}
        printf("==========================================================\n");
    }
    
    
return 0;
}
