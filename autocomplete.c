#include "autocomplete.h"

trie_node_pair prefix_node(trie_t *root, char *prefix)
{
	int len = strlen(prefix);
	trie_t *node = root;

	for (int level = 0; level < len; ++level) {
		if (!node->subtrie[prefix[level] - 'a'])
			return (trie_node_pair) {NULL, 0};

		node = node->subtrie[prefix[level] - 'a'];
	}

	return (trie_node_pair){node, len};
}

int traverse_lex(trie_t *node, char *prefix, char *cur_word, int index)
{
	if (node->is_end_of_word) {
		printf("%s\n", cur_word);
		return 1;
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->subtrie[i]) {
			char next_word[WORD_LEN];
			strncpy(next_word, cur_word, WORD_LEN);

			next_word[index] = 'a' + i;
			next_word[index + 1] = '\0';

			return traverse_lex(node->subtrie[i], prefix, next_word, index + 1);
		}
	}

	return 0;
}

int traverse_short(trie_t *node, char *prefix, int index)
{
	trie_node_pair queue[WORD_LEN * ALPHABET_SIZE];
	char queue_words[WORD_LEN * ALPHABET_SIZE][WORD_LEN];
	int front = 0, back = 0;

	queue[back] = (trie_node_pair){node, index};
	strncpy(queue_words[back], prefix, WORD_LEN);
	back++;

	while (front != back) {
		trie_node_pair pair = queue[front];
		char *cur_word = queue_words[front];
		front++;

		trie_t *current_node = pair.node;
		int current_index = pair.index;

		if (current_node->is_end_of_word) {
			printf("%s\n", cur_word);
			return 1;
		}

		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			if (current_node->subtrie[i]) {
				char next_word[WORD_LEN];
				strncpy(next_word, cur_word, WORD_LEN);
				next_word[current_index] = 'a' + i;
				next_word[current_index + 1] = '\0';

				queue[back] = (trie_node_pair)
							  {current_node->subtrie[i], current_index + 1};
				strncpy(queue_words[back], next_word, WORD_LEN);
				back++;
			}
		}
	}
	return 0;
}

void traverse_freq(trie_t *node, char *prefix, char *cur_word, int index,
				   int *max_freq, char *max_word)
{
	if (node->is_end_of_word && node->freq > *max_freq) {
		*max_freq = node->freq;
		strncpy(max_word, cur_word, WORD_LEN);
	}

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->subtrie[i]) {
			char next_word[WORD_LEN];
			strncpy(next_word, cur_word, WORD_LEN);
			next_word[index] = 'a' + i;
			next_word[index + 1] = '\0';

			traverse_freq(node->subtrie[i], prefix, next_word, index + 1,
						  max_freq, max_word);
		}
	}
}

// all words that have the given prefix and the given criterion
void command_autocomplete(trie_t *root)
{
	char prefix[WORD_LEN];
	scanf("%s", prefix);

	int crit = 0;
	scanf("%d", &crit);

	trie_node_pair pair = prefix_node(root, prefix);

	if (!pair.node) {
		printf("No words found\n");
		return;
	}

	char cur_word[WORD_LEN];
	strncpy(cur_word, prefix, WORD_LEN);

	switch (crit) {
	// the smalles lexicographical word with the given prefix
	case 1: {
		if (!traverse_lex(pair.node, prefix, cur_word, pair.index))
			printf("No words found\n");
		break;
	}
	// the shortest word with the given prefix
	case 2: {
		if (!traverse_short(pair.node, cur_word, pair.index))
			printf("No words found\n");
		break;
	}
	// the most frequently used word with the given prefix (if tie, the smallest
	// lexicographical word is returned)
	case 3: {
		int max_freq = -1;
		char max_word[WORD_LEN];
		traverse_freq(pair.node, prefix, cur_word, pair.index,
					  &max_freq, max_word);

		if (max_freq != -1)
			printf("%s\n", max_word);
		else
			printf("No words found\n");

		break;
	}
	// all of the above
	case 0: {
		if (!traverse_lex(pair.node, prefix, cur_word, pair.index))
			printf("No words found\n");

		if (!traverse_short(pair.node, cur_word, pair.index))
			printf("No words found\n");

		int max_freq = -1;
		char max_word[WORD_LEN];
		traverse_freq(pair.node, prefix, cur_word, pair.index,
					  &max_freq, max_word);

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


