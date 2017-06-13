#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef enum { TRUE, FALSE } boolean;

typedef struct TrieNode{
    struct TrieNode *children; 
    char label;
    boolean isEndOfWord;
} TrieNode;

TrieNode* createNode(){
   TrieNode* tnode=(TrieNode*)malloc(sizeof(TrieNode)); 
   tnode->children=(TrieNode*)malloc(sizeof(TrieNode)*ALPHABET_SIZE);  
   return tnode;
}

//strLen as an integer.
int strLen(char* string){
  return (int)strlen(string);	
}

//Get the substring [0:String.len-1]
char* prifString(char* data){     
	int length=strlen(data);
	char* new=(char*)malloc(sizeof(char)*(length-1));
	int i;

	for(i=0; i<length-1; i++){
		new[i]=data[i];	
	}		
return new;
}

//get the substring [1:String.len]
char* subString(char* data){     
	int length=strlen(data);
	char* new=(char*)malloc(sizeof(char)*(length-1));
	int i;

	for(i=1; i<length; i++){
		new[i-1]=data[i];	
	}	
	
return new;
}

void insert(TrieNode *root,char *word){
	
	if(strLen(word) != 0){
		 //Get the corresponding child  object.	
	     TrieNode* child=&(root->children[word[0]-97]);
         
         if(child->label == 0){	  //No label assigned to child. 
		   
		   child->label=word[0];  //Update the child
		   child->children=(TrieNode*)malloc(sizeof(TrieNode)*ALPHABET_SIZE);		   
		   
		   if(strLen(word) == 1){ //End of the word
			  child->isEndOfWord=TRUE;  
		   }else{ //If not insert a substring of the word to the Trie.
			  child->isEndOfWord=FALSE; 
		      insert(child,subString(word));
		   }		   
		   		    
		 }else if(child->label == word[0]){ //Sub string of word
		    if(strLen(word) == 1){ //End of the new Substring
			  child->isEndOfWord=TRUE; 
		    }else{	 //Add mode string to the Tire
			  insert(child,subString(word));		 		 
			}
		 }	
    }else{
	    return;	
	}
}

//Print array helper function for printWors.
void printArray(int arr[],int size,char* prif){
	int i;
	
	for(i=0;i<strLen(prif); i++){
		printf("%c",(char)prif[i]);
	}
	for(i=0;i<size;i++){
		if(arr[i] != '#'){
			printf("%c",(char)arr[i]);	
		}
	}
	printf("\n");
}

void printWords(TrieNode* root,int path[],int pathLen,char* pref){
   
   path[pathLen]=root->label; //Append the character to the path[]
   pathLen++;
   
   if(root->isEndOfWord == TRUE){ //If the node isEnd then print the word.
	   printArray(path,pathLen,prifString(pref));
   if(root->children != NULL){ //Check there are childrens to the node with longer length words.
	   int i;	   
	   for(i=0; i<ALPHABET_SIZE; i++){
		 TrieNode* child=&(root->children[i]);		 
		 if(child->label != 0){
		    printWords(child,path,pathLen,pref); //Call all valid childern.
		 }   		   
	   }	   
   }   
   }else{ //If it is not the end call all valid childrens	   
	   int i;	   
	   for(i=0; i<ALPHABET_SIZE; i++){
		 TrieNode* child=&(root->children[i]);
		 if(child->label != 0){
		    printWords(child,path,pathLen,pref);	 
		 }   		   
	   }	   
   }  
}

//Given a node print all paths bellow it
void printPaths(TrieNode* node,char* pref) 
{
  int path[1000];
  printWords(node, path, 0,pref);
}

//search for the last node in the string path 
TrieNode* search(TrieNode *root,char* substring){
  
  if(strLen(substring) == 1){ //The last label to check
	 TrieNode* child=&(root->children[substring[0]-97]); //Get the corresponding child
	 
	 if(child->label == substring[0]){
	    return child;	//The correct sub tree found. 
     }else{
	    return NULL;	 
	 }	  
  }else{
	 TrieNode* child=&(root->children[substring[0]-97]);
	 
	 if(child->label == substring[0]){
	    return search(child,subString(substring));//Travel through the tree	 
     }else{
	    return NULL;	 
	 }	   	  
  }  
}

//travel through the string and find all maching words.
void traverse(char* prifix,TrieNode* root){
   TrieNode* subtree=search(root,prifix);
   if(subtree != NULL){
	printPaths(subtree,prifix);	
   }
}
