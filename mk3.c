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




// char *append(char *slice, char part)
// {
// 	char *str = malloc(sizeof(char) * (strlen(slice) + 2));

// 	int i = 0;
// 	while (slice[i] != '\0') {
// 		str[i] = slice[i];
// 		i++;
// 	}

// 	str[i++] = part;
// 	str[i] = '\0';

// 	return str;
// }

// void print(trie *node_trie, char *slice)
// {
// 	if (node_trie == NULL)
// 		return;

// 	if (node_trie->isEndOfWord)
// 		printf("%s\n", slice);

// 	for (int i = 0; i < ALPHABET_SIZE; ++i) {
// 		if (node_trie->subtrie[i] != NULL)
// 			print(node_trie->subtrie[i], append(slice, i + 97));
// 	}
// }

// void autocomplete(trie *node_trie, char *prefix)
// {
// 	int len = strlen(prefix);
// 	for (int i = 0; i < len; ++i)
// 		node_trie = node_trie->subtrie[prefix[i] % 97];

// 	print(node_trie, prefix);
// }






	// char word1[] = "hello";
	// char word2[] = "world";
	// char word3[] = "hell";
	// char word4[] = "help";
	// char word5[] = "he";

	// trie_insert(&root, word1);
	// trie_insert(&root, word2);
	// trie_insert(&root, word3);
	// trie_insert(&root, word4);
	// trie_insert(&root, word5);

	// char input1[] = "he";
	// char input2[] = "hel";
	// char input3[] = "help";
	// char input4[] = "hello";
	// char input5[] = "helloo";

	// printf (">> ");
	// autocomplete (&root, input1);

	// printf (">> ");
	// autocomplete (&root, input2);

	// printf (">> ");
	// autocomplete (&root, input3);

	// printf (">> ");
	// autocomplete (&root, input4);

	// printf (">> ");
	// autocomplete (&root, input5);

	// in case switch fails and memory has to be free'd