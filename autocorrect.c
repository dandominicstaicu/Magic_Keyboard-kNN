#include "autocorrect.h"

// all words that can be obtained by changing at most k characters
// only changing, not adding or removing
void command_autocorrect(trie_t *root)
{
	char word[WORD_LEN];
	scanf("%s", word);

	int k; // number of characters that can be changed
	scanf("%d", &k);

	traverse_with_limit(root, word, "", 0, k, 0);
}

void traverse_with_limit(trie_t *node, char *word, char *cur_word, int index,
						 int k, int cur_dist)
{
	int word_len = strlen(word);
	if (index > word_len)
		return;

	if (cur_dist > k)
		return;

	if (index == word_len && node->is_end_of_word && cur_dist <= k)
		printf("%s\n", cur_word);

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->subtrie[i]) {
			char next_word[WORD_LEN];
			strncpy(next_word, cur_word, WORD_LEN);
			next_word[index] = 'a' + i;
			next_word[index + 1] = '\0';

			int next_dist = cur_dist;
			if (index < word_len) {
				if (word[index] != next_word[index])
					next_dist += 1;
			}

			traverse_with_limit(node->subtrie[i], word, next_word, index + 1,
								k, next_dist);
		}
	}
}
