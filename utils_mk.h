#ifndef _UTILS_MK_H_
#define _UTILS_MK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ALPHABET_SIZE 26
#define WORD_LEN 50
#define COMMAND_LEN 15
#define TRUE 1

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);				        \
		}							\
	} while (0)

typedef struct trie_t trie_t;
struct trie_t {
	trie_t *subtrie[ALPHABET_SIZE];
	int is_end_of_word;
	int freq;
};

typedef struct trie_node_pair trie_node_pair;
struct trie_node_pair {
	trie_t *node;
	int index;
};

int hash_command(char *command);

#endif // _UTILS_MK_H_