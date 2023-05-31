#ifndef _RANGE_SEARCH_H_
#define _RANGE_SEARCH_H_

#include "utils_kNN.h"

void range_search(kd_node_t *root, int *start, int *end, int k, int depth);

#endif
