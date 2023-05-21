#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define WORD_LEN 50
#define COMMAND_LEN 15
#define TRUE 1

typedef struct trie trie;
struct trie {
	trie *subtrie[ALPHABET_SIZE];
	int isEndOfWord;
};

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

void trie_insert(trie *node_trie, char *word)
{
	trie *root = node_trie;

	int len = strlen(word);

	for (int i = 0; i < len; ++i) {
		trie *current = node_trie->subtrie[word[i] % 97];

		if (current	== NULL) {
			current = (trie *)malloc(sizeof(trie));
			current->isEndOfWord = 0;

			for (int j = 0; j < ALPHABET_SIZE; ++j)
				current->subtrie[j] = NULL;
		}

		if (i + 1 == len)
			current->isEndOfWord = 1;

		node_trie->subtrie[word[i] % 97] = current;
		node_trie = node_trie->subtrie[word[i] % 97];
	}

	node_trie = root;
}

char *append(char *slice, char part)
{
	char *str = malloc(sizeof(char) * (strlen(slice) + 2));

	int i = 0;
	while (slice[i] != '\0') {
		str[i] = slice[i];
		i++;
	}

	str[i++] = part;
	str[i] = '\0';

	return str;
}

void print(trie *node_trie, char *slice)
{
	if (node_trie == NULL)
		return;

	if (node_trie->isEndOfWord)
		printf("%s\n", slice);

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node_trie->subtrie[i] != NULL)
			print(node_trie->subtrie[i], append(slice, i + 97));
	}
}

void autocomplete(trie *node_trie, char *prefix)
{
	int len = strlen(prefix);
	for (int i = 0; i < len; ++i)
		node_trie = node_trie->subtrie[prefix[i] % 97];

	print(node_trie, prefix);
}

// save the word and increment it's frequency
void command_insert(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	trie_insert(&root, word);
}

// read words from a given file and insert them into the trie
void command_load(trie *root)
{
	char filename[WORD_LEN];
	scanf("%s", filename);

	FILE *file = fopen(filename, "rt");

	if (file == NULL) {
		fprintf(stderr, "File not found\n");
		return;
	}

	char word[WORD_LEN];
	while (fscanf(file, "%s", word) != EOF)
		trie_insert(&root, word);

	fclose(file);
}

// remove a word from the trie and free the memory
// if word doesn't exist, do nothing
void command_remove(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	//TODO
}

// all words that can be obtained by changing at most k characters
// only changing, not adding or removing
void command_autocorrect(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	int k; // number of characters that can be changed
	scanf("%d", &k);

	//TODO
}

// all words that have the given prefix and the given criterion
void command_autocomplete(trie *root)
{
	char prefix[WORD_LEN];
	scanf("%s", prefix);

	short crit = 0;
	scanf("%d", &crit);

	switch (crit){
	// the smalles lexicographical word with the given prefix 
	case 1:
		
		break;
	
	// the shortest word with the given prefix
	case 2:

		break;
	
	// the most frequently used word with the given prefix (if tie, the smallest
	// lexicographical word is returned)
	case 3:

		break;

	// all of the above
	case 0:

		break;
	
	default:
		fprintf(stderr, "Invalid criterion\n");
		break;
	}

}

// free the memory
void command_exit(trie *root)
{
	//TODO
}

int main(void)
{
	trie root;
	root.isEndOfWord = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		root.subtrie[i] = NULL;

	char command[COMMAND_LEN];
	scanf("%s", command);

	while (TRUE) {
		switch (hash_command(command)) {
		case 0:
			command_insert(&root);
			break;
		case 1:
			command_load(&root);
			break;
		case 2:
			command_remove(&root);
			break;
		case 3:
			command_autocorrect(&root);
			break;
		case 4:
			command_autocomplete(&root);
			break;
		case 5:
			command_exit(&root);
			return 0;
		default:
			fprintf(stderr, "Invalid command\n");
			break;
		}

		scanf("%s", command);
	}

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
	command_exit(&root);
	return 0;
}