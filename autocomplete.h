#ifndef _AUTOCOMPLETE_H_
#define _AUTOCOMPLETE_H_

#include "utils_mk.h"

trie_node_pair prefix_node(trie_t *root, char *prefix);

int traverse_lex(trie_t *node, char *prefix, char *cur_word, int index);

int traverse_short(trie_t *node, char *prefix, int index);

void traverse_freq(trie_t *node, char *prefix, char *cur_word, int index,
				   int *max_freq, char *max_word);

void command_autocomplete(trie_t *root);

#endif
