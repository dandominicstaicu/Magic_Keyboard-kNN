#ifndef _TIRE_COMMANDS_H_
#define _TIRE_COMMANDS_H_

#include "utils_mk.h"

void command_insert(trie_t *root);

void command_load(trie_t *root);

void command_remove(trie_t *root);

void trie_insert(trie_t *node_trie, char *word);

void trie_remove(trie_t *root, char *word);

void command_exit(trie_t *root);

void trie_free(trie_t *node);

#endif // _TIRE_COMMANDS_H_
