#ifndef _kNN_COMMANDS_H_
#define _kNN_COMMANDS_H_

#include "utils_kNN.h"
#include "kNN_operations.h"
#include "range_search.h"
#include "nearest_neighbor.h"

void command_load(kd_tree *tree, int *n, int *k);

void command_nn(kd_tree *tree, int k);

void command_rs(kd_tree *tree, int k);

void command_exit(kd_tree *tree);

#endif
