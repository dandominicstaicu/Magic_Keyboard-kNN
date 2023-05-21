#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define WORD_LEN 50

typedef struct trie trie;
struct trie {
	trie *subtrie[ALPHABET_SIZE];
	int isEndOfWord;
};

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

int main(void)
{
	trie root;
	root.isEndOfWord = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		root.subtrie[i] = NULL;

	// char word[WORD_LEN];

	char word1[] = "hello";
	char word2[] = "world";
	char word3[] = "hell";
	char word4[] = "help";
	char word5[] = "he";

	trie_insert(&root, word1);
	trie_insert(&root, word2);
	trie_insert(&root, word3);
	trie_insert(&root, word4);
	trie_insert(&root, word5);

	char input1[] = "he";
	char input2[] = "hel";
	char input3[] = "help";
	char input4[] = "hello";
	char input5[] = "helloo";

	printf (">> ");
	autocomplete (&root, input1);

	printf (">> ");
	autocomplete (&root, input2);

	printf (">> ");
	autocomplete (&root, input3);

	printf (">> ");
	autocomplete (&root, input4);

	printf (">> ");
	autocomplete (&root, input5);

	return 0;
}