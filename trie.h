#ifndef _TIRIE_H_
#define _TIRIE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
    int frequency;
} TrieNode;

trie_node_t *trie_create_node(trie_t *trie);

#endif