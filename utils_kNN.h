#ifndef _UTILS_kNN_H_
#define _UTILS_kNN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define COMMAND_LEN 10
#define TRUE 1
#define FALSE 0
#define FILENAME_LEN 50

// macro for error handling
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);				        \
		}							\
	} while (0)

// node of the kd tree
typedef struct kd_node_t kd_node_t;
struct kd_node_t {
	int *point;
	kd_node_t *left;
	kd_node_t *right;
};

// kd tree
typedef struct kd_tree kd_tree;
struct kd_tree {
	kd_node_t *root;
};

int hash_command(char *command);

#endif
