#ifndef _AUTOCORRECT_H_
#define _AUTOCORRECT_H_

#include "utils_mk.h"

void command_autocorrect(trie_t *root);

void traverse_with_limit(trie_t *node, char *word, char *cur_word, int index,
						 int k, int cur_dist);

#endif
