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
	int is_end_of_word;
	int freq;
};

typedef struct trie_node_pair trie_node_pair;
struct trie_node_pair {
	trie *node;
	int index;
};

trie_node_pair prefix_node(trie *root, char *prefix)
{
	int len = strlen(prefix);
	trie *node = root;

	for (int level = 0; level < len; ++level) {
		if (!node->subtrie[prefix[level] - 'a'])
			return (trie_node_pair) {NULL, 0};

		node = node->subtrie[prefix[level] - 'a'];
	}

	return (trie_node_pair){node, len};
}

void traverse_lex(trie *node, char *prefix, char *cur_word, int index)
{
	if (node->is_end_of_word) {
		printf("%s\n", cur_word);
		return;
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->subtrie[i] != NULL) {
			char next_word[WORD_LEN];
			strncpy(next_word, cur_word, WORD_LEN);

			next_word[index] = 'a' + i;
			next_word[index + 1] = '\0';

			traverse_lex(node->subtrie[i], prefix, next_word, index + 1);
			return;
		}
	}
}

void traverse_short(trie *node, char *cur_word, int index)
{
	trie_node_pair queue[WORD_LEN * ALPHABET_SIZE];
	int front = 0, back = 0;


	queue[back++] = (trie_node_pair){node, index};

	while (front != back) {
		trie_node_pair pair = queue[front++];
		trie *current_node = pair.node;
		int current_index = pair.index;

		if (current_node->is_end_of_word) {
			cur_word[current_index] = '\0';
			printf("%s\n", cur_word);
			return;
		}

		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			if (current_node->subtrie[i] != NULL) {
				char next_word[WORD_LEN];
				strncpy(next_word, cur_word, WORD_LEN);
				next_word[current_index] = 'a' + i;

				queue[back++] = (trie_node_pair){current_node->subtrie[i], current_index + 1};
			}
		}
	}
}

void traverse_freq(trie *node, char *prefix, char *cur_word, int index, int *max_freq, char *max_word) {
    if (node->is_end_of_word && node->freq > *max_freq) {
        *max_freq = node->freq;
        strncpy(max_word, cur_word, WORD_LEN);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->subtrie[i] != NULL) {
            char next_word[WORD_LEN];
            strncpy(next_word, cur_word, WORD_LEN);
            next_word[index] = 'a' + i;
            next_word[index + 1] = '\0';

            traverse_freq(node->subtrie[i], prefix, next_word, index + 1, max_freq, max_word);
        }
    }
}

int hash_command(char *command)
{
	if (strcmp(command, "INSERT") == 0)
		return 0;
	else if (strcmp(command, "LOAD") == 0)
		return 1;
	else if (strcmp(command, "REMOVE") == 0)
		return 2;
	else if (strcmp(command, "AUTOCORRECT")== 0)
		return 3;
	else if (strcmp(command, "AUTOCOMPLETE") == 0)
		return 4;
	else if (strcmp(command, "EXIT") == 0)
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
			current->is_end_of_word = 0;
			current->freq = 0;

			for (int j = 0; j < ALPHABET_SIZE; ++j)
				current->subtrie[j] = NULL;
		}

		if (i + 1 == len){
			current->is_end_of_word = 1;
			current->freq++;
		}
		node_trie->subtrie[word[i] % 97] = current;
		node_trie = node_trie->subtrie[word[i] % 97];
	}

	node_trie = root;
}

void trie_remove(trie *root, char *word)
{
	int len = strlen(word);
	trie *node = root;
	trie *path[WORD_LEN];

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
	if (node != NULL && node->is_end_of_word == 0)
		return;

	// word is found and it's in the trie; remove it; mark it as not end of word
	node->is_end_of_word = 0;

	// if it is a non leaf node, do nothing, return
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		if (node->subtrie[i] != NULL)
			return;

	// if it's a leaf, start from the deepest node and delete backwards
	for (int level = len - 1; level >= 0; --level) {
		trie *parent = path[level];
		if (parent != NULL) {
			parent->subtrie[word[level] - 'a'] = NULL;
			free(node);
			node = parent;
		
		// if parent is a non leaf node, stop
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if (parent->subtrie[i] != NULL)
				return;
		}
	}
}

void traverse_with_limit(trie* node, char* word, char* cur_word, int index, int k, int cur_dist) {
    int word_len = strlen(word);
	if (index > word_len)
        return;

    if (cur_dist > k)
        return;

    if (index == word_len && node->is_end_of_word && cur_dist <= k)
        printf("%s\n", cur_word);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->subtrie[i] != NULL) {
            char next_word[WORD_LEN];
            strncpy(next_word, cur_word, WORD_LEN);
            next_word[index] = 'a' + i;
            next_word[index + 1] = '\0';

            int next_dist = cur_dist;
            if (index < word_len) {
                if (word[index] != next_word[index])
                    next_dist += 1;
            }

            traverse_with_limit(node->subtrie[i], word, next_word, index + 1, k, next_dist);
        }
    }
}

// save the word and increment it's frequency
void command_insert(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	trie_insert(root, word);
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
		trie_insert(root, word);

	fclose(file);
}

// remove a word from the trie and free the memory
// if word doesn't exist, do nothing
void command_remove(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	trie_remove(root, word);
}

// all words that can be obtained by changing at most k characters
// only changing, not adding or removing
void command_autocorrect(trie *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	int k; // number of characters that can be changed
	scanf("%d", &k);

	traverse_with_limit(root, word, "", 0, k, 0);
}

// all words that have the given prefix and the given criterion
void command_autocomplete(trie *root)
{
	char prefix[WORD_LEN];
	scanf("%s", prefix);

	int crit = 0;
	scanf("%d", &crit);

	trie_node_pair pair = prefix_node(root, prefix);

	if (pair.node == NULL) {
		fprintf(stderr, "No words found\n");
		return;
	}

	char cur_word[WORD_LEN];
	strncpy(cur_word, prefix, WORD_LEN);

	switch (crit){
	// the smalles lexicographical word with the given prefix 
	case 1: {
		traverse_lex(pair.node, prefix, cur_word, pair.index);
		break;
	}
	// the shortest word with the given prefix
	case 2: {
		traverse_short(pair.node, cur_word, pair.index);
		break;
	}
	// the most frequently used word with the given prefix (if tie, the smallest
	// lexicographical word is returned)
	case 3: {
		int max_freq = -1;
		char max_word[WORD_LEN];
		traverse_freq(pair.node, prefix, cur_word, pair.index, &max_freq, max_word);

		if (max_freq != -1)
			printf("%s\n", max_word);
		else
			printf("No words found\n");

		break;
	}
	// all of the above
	case 0: {
		traverse_lex(pair.node, prefix, cur_word, pair.index);
        traverse_short(pair.node, cur_word, pair.index);
        
		int max_freq = -1;
        char max_word[WORD_LEN];
        traverse_freq(pair.node, prefix, cur_word, pair.index, &max_freq, max_word);
        
		if (max_freq != -1) 
			printf("%s\n", max_word);
        else 
			printf("No words found\n");

		break;
	}
	default:
		fprintf(stderr, "Invalid criterion\n");
		break;
	}

	//if word doesn't exist, print "No words found"
	// in case of criterion 0, "No words found" can be printed multiple times

}

// free the memory
void command_exit(trie *root)
{
	//TODO
}

int main(void)
{
	trie root;
	root.is_end_of_word = 0;
	root.freq = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		root.subtrie[i] = NULL;

	char command[COMMAND_LEN];
	scanf("%s", command);

	while (TRUE) {
		// printf("command ind: %d\n", hash_command(command));
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

	command_exit(&root);
	return 0;
}