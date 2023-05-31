#include "trie_commands.h"

// save the word and increment it's frequency
void command_insert(trie_t *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	trie_insert(root, word);
}

// read words from a given file and insert them into the trie
void command_load(trie_t *root)
{
	char filename[WORD_LEN];
	scanf("%s", filename);

	FILE *file = fopen(filename, "rt");
	DIE(!file, "File not found\n");

	char word[WORD_LEN];
	while (fscanf(file, "%s", word) != EOF)
		trie_insert(root, word);

	fclose(file);
}

// remove a word from the trie_t and free the memory
// if word doesn't exist, do nothing
void command_remove(trie_t *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	trie_remove(root, word);
}

void trie_insert(trie_t *node_trie, char *word)
{
	trie_t *root = node_trie;

	int len = strlen(word);

	for (int i = 0; i < len; ++i) {
		trie_t *current = node_trie->subtrie[word[i] % 97];

		if (!current) {
			current = (trie_t *)malloc(sizeof(trie_t));
			DIE(!current, "malloc failed in trie_insert");

			current->is_end_of_word = 0;
			current->freq = 0;

			for (int j = 0; j < ALPHABET_SIZE; ++j)
				current->subtrie[j] = NULL;
		}

		if (i + 1 == len) {
			current->is_end_of_word = 1;
			current->freq++;
		}
		node_trie->subtrie[word[i] % 97] = current;
		node_trie = node_trie->subtrie[word[i] % 97];
	}

	node_trie = root;
}

void trie_remove(trie_t *root, char *word)
{
	int len = strlen(word);
	trie_t *node = root;
	trie_t *path[WORD_LEN];

	// initialize path
	for (int level = 0; level < len; ++level)
		path[level] = NULL;

	// check if word exists and get the path from root to the last char of word
	for (int level = 0; level < len; ++level) {
		if (!node->subtrie[word[level] - 'a'])
			return; // word doesn't exist, do nothing

		path[level] = node;
		node = node->subtrie[word[level] - 'a'];
	}

	// word is found, but it's not in the tire; do nothing
	if (node && node->is_end_of_word == 0)
		return;

	// word is found and it's in the trie; remove it; mark it as not end of word
	node->is_end_of_word = 0;

	// if it is a non leaf node, do nothing, return
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		if (node->subtrie[i])
			return;

	// if it's a leaf, start from the deepest node and delete backwards
	for (int level = len - 1; level >= 0; --level) {
		trie_t *parent = path[level];
		if (parent) {
			parent->subtrie[word[level] - 'a'] = NULL;
			free(node);
			node = parent;

		// if parent is a non leaf node, stop
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if (parent->subtrie[i])
				return;
		}
	}
}

// free the memory
void command_exit(trie_t *root)
{
	trie_free(root);
}

void trie_free(trie_t *node)
{
	// Base case: NULL node
	if (!node)
		return;

	// Recursive case: visit all children
	for (int i = 0; i < ALPHABET_SIZE; i++)
		trie_free(node->subtrie[i]);

	// Now that all children are free, free the node itself
	free(node);
}
