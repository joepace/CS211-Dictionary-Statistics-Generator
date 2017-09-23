#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

struct TrieNode{
	struct TrieNode * children[26];
	
	
	int occurrences;
	int prefixes;
	bool end;
};

void readDict(FILE *dict_file);

void readData(FILE * data_file);

void matchStr(char* str);

struct TrieNode * newTree();

void printResult();

void printResultHelper(FILE* filepointer, struct TrieNode* triepointer, char word[100], int level);


void insert(char * key);
void freeAllNodes(struct TrieNode * pointer);

