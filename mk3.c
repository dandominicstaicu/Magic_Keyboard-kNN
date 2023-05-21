#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LEN 100
#define TRUE 1
#define ALPHABET_SIZE 26
#define WORD_LEN 50

int hash_command(char *command)
{
	if (strcmp(command, "INSERT"))
		return 0;
	else if (strcmp(command, "LOAD"))
		return 1;
	else if (strcmp(command, "REMOVE"))
		return 2;
	else if (strcmp(command, "AUTOCORRECT"))
		return 3;
	else if (strcmp(command, "AUTOCOMPLETE"))
		return 4;
	else if (strcmp(command, "EXIT"))
		return 5;

	return -1;
}

typedef struct trie_node trie_node;
struct trie_node {
    trie_node *children[ALPHABET_SIZE];
    int isEndOfWord;
    int frequency;
};

trie_node *get_node(void)
{
    trie_node *new_node = (trie_node *)malloc(sizeof(trie_node));
    new_node->isEndOfWord = 0;
    new_node->frequency = 0;
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
        new_node->children[i] = NULL;
    
    return new_node;
}

void trie_insert(trie_node *root, const char *word) {
    int length = strlen(word);
    int index;

    trie_node *node = root;
    
    for (int level = 0; level < length; level++) {
        index = word[level] - 'a';
        if (!node->children[index])
            node->children[index] = get_node();

        node = node->children[index];
    }

    node->isEndOfWord = 1;
    node->frequency++;
}

int trie_search(trie_node *root, char *word) {
	int len = strlen(word);
}

void insert_read(trie_node *root)
{
	char word[WORD_LEN];
	scanf("%s", word);
	
	// Insert word into Trie
	insert(root, word);
}



// Your task now is to implement the rest of the operations such as:
// 1. Load function to read from file
// 2. Remove function to remove a word
// 3. Autocorrect function to find similar words
// 4. Autocomplete function to suggest completions
// 5. Exit function to free memory

int main(void)
{	
	// Create root of Trie
    trie_node *root = get_node();

	char command[COMMAND_LEN];

	scanf("%s", command);

	while (TRUE) {
		switch (hash_command(command)) {
		case 0:
			insert_read(root);
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:

			return 0;
		default:
			fprintf(stderr, "Invalid command\n");
			break;
		}

		scanf("%s", command);
	}
	

	//free all just before return 0
	return 0;
}
