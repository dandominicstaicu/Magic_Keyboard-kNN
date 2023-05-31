#ifndef _kNN_operations_H_
#define _kNN_operations_H_

#include "utils_kNN.h"

kd_tree *create_tree(void);

kd_node_t *create_node(int *point, int k);

kd_node_t *insert_node(kd_node_t *root, int *point, int k, int depth);

void free_tree(kd_node_t *node);

#endif