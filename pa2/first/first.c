#include"first.h"

struct TrieNode * root = NULL;
int filenum = 0;

/*
The readDict() function uses a pointer to the dictionary file to read the file character by character and parses out the unique dictionary words. These words are then added to the Trie structure by calling insert() and passing the word to be added.
*/

void readDict(FILE *dict_file){
	char current = '\0';
	char word[72];
	int index = 0;
	
	while(true){
		current = fgetc(dict_file);
		if(isalpha(current) == false || current == EOF){
			if(index > 0){
				word[index] = '\0';
				insert(word);
				index = 0;
			
			}
			
			if(current == EOF){
				break;
			}
		}
		else{
			word[index] = tolower(current);
			index++;
		}
	}
}

/*
	The readData() function takes in a pointer to the file containing the data and parses words from the file. The words found will then be sent to the matchStr() function as parameters to search the Trie structure to see if the word is a prefix, superword, or not included in the dictionary.
*/

void readData(FILE * data_file){
	char current = '\0';
	char word[72];
	int index = 0;
	bool run = true;
	
	
	while(run){
		current = fgetc(data_file);
		if(isalpha(current) == false || current == EOF){
			if(index > 0){
				word[index] = '\0';
				matchStr(word);
				index = 0;
				
			}
			
			if(current == EOF){
				run = false;
			}
		}
		else{
			
			word[index] = tolower(current);
			index++;
		}
	}
	
}

/*
	The matchStr() function takes an array of characters and searches for it in the dictionary (Trie structure). Through traversing the Trie, the function will determine the number of prefixes and superwords of the unique dictionary words.
*/

void matchStr(char* str){
	int height = 0;
	int length = strlen(str);
	int index = 0;
	
	if(root == NULL){
		return;
	}
	
	struct TrieNode * pointer;
	
	pointer = root;
	
	//For some reason, this line is needed to make the program run. Not sure why, to be honest.
	printf(" ");
	
	//Traverse Trie
	for(height = 0; height < length; height++){
		
		index = (int)str[height] - (int)'a';
		pointer = pointer->children[index];
		if((pointer) == NULL){
			return;
		}
		
		if(height < (length - 1)){
			pointer->prefixes += 1;		
		}
	}
	
	pointer->occurrences += 1;
}

/*
	The newTree() function creates a pointer to a new Trie tree or sub-tree, depending on what variable the new pointer is being saved to. The fields associated with the structure TrieNode are also initialized.

*/
struct TrieNode * newTree(){
	struct TrieNode * pointer = (struct TrieNode *) malloc(sizeof(struct TrieNode));
	int i = 0;
	
	if(pointer){
		
		pointer->occurrences = 0;
		pointer->prefixes = 0;
		pointer->end = false;
		
		for(i = 0; i < 26; i++){
			pointer->children[i] = NULL;
		}
	}
	return pointer;
}

/*
	The printResult() function does what its name implies - it will create an out text file in which the statistical results of the program (number of prefixes and superwords) will be printed. This function will call printResultHelper(), which will retrieve the results from the data fields (prefix and superword) from the leaves of Trie structure.
*/

void printResult(){
	filenum++;
	char file_name[50];
	char word[72];
	int level = 0;
	
	
	sprintf(file_name, "out%d.txt", filenum);
	
	FILE* new_file;
	new_file = fopen(file_name, "w"); 
	
	
	printResultHelper(new_file, root, word, level);

	
	fclose(new_file);
	
}

/*
Given the pointer to an output file and the pointer to the Trie structure, printResultHelper() will traverse the tree recursively and read the data into an output file.
*/

void printResultHelper(FILE* filepointer, struct TrieNode* triepointer, char word[72], int level){
	
	if(triepointer == NULL){
		
		return;
	}
	
	int i;
	
	if(triepointer->end == true){
		word[level] = '\0';
		fprintf(filepointer, "%s %d %d\n", word, triepointer->occurrences, triepointer->prefixes);
	
	}
	
	for(i = 0; i < 26; i++){
		if(triepointer->children[i] != NULL){
			word[level] = i + 97;
		}
		
		printResultHelper(filepointer, triepointer->children[i], word, level + 1);
		
	}
}



/*
	The insert() function traverses the Trie and checks to see if the letter in the key is already in the Trie. If not, it will be added to the tree. Since the array for children has 26 indexes, index 0 will signify 'a', index 1 will be 'b', and so on until the end of the alphabet. When the end of the word is reached, it will be added to the word field of the pointer.
*/

void insert(char * key){
	int height = 0;
	int length = strlen(key);
	int index = 0;
	
	if(root == NULL){
		root = newTree();
	}

	struct TrieNode *traversal_pointer = root;
	
	//Traverse tree and add nodes as needed
	for(height = 0; height < length; height++){
		index = (int)key[height] - (int)'a';
		
		if(traversal_pointer -> children[index] == NULL){
			traversal_pointer -> children[index] = newTree();
			
		}
		
		traversal_pointer = traversal_pointer->children[index];
	}
	
	traversal_pointer->end = true;
}

/*
	The freeAllNodes() function will recursively traverse the entire Trie tree and free each node recursively by passing a pointer to each node in the structure as a parameter.
*/
void freeAllNodes(struct TrieNode * pointer){
	
	
	int i;
	
	//Traverses until the end of the Trie branch
	for(i = 0; i < 26; i++){
		if(pointer->children[i]){
			if(pointer->children[i]){
				freeAllNodes(pointer -> children[i]);
			}
		}
	}
	
	
	free(pointer);

}

/*
	The main function that serves as the driver for this program.
*/

int main(int argc, char** argv){
	
	//Checks that only input argument is the map file
	if(argc != 2){
		printf("invalid input\n");
		exit(0);
	}
	char* fileName = argv[1];
	
	FILE* file_pointer = fopen(fileName, "r");
	
	FILE* dict_file;
	char dict_name[20];
	
	FILE* data_file;
	char data_name[20];
	
	
	
	while(fscanf(file_pointer, "%s %s\n", dict_name, data_name) != EOF){
	
		
		dict_file = fopen(dict_name, "r");
		data_file = fopen(data_name, "r");
		
		root = newTree();
		
		
		//Checking validity/existence of files 
		if (dict_file == NULL || data_file == NULL){
			printf("invalid input\n");
			exit(0);
		}
		
		readDict(dict_file);
		readData(data_file);
		printResult();
		
		freeAllNodes(root);
		fclose(dict_file);
		fclose(data_file);
	}
	fclose(file_pointer);
	
	return 0;
}
