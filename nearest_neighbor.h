#ifndef _NEAREST_NEIGHBOR_H_
#define _NEAREST_NEIGHBOR_H_

#include "utils_kNN.h"

double distance(int *point1, int *point2, int k);

void nearest_neighbor_search(kd_node_t *root, int *target, int k, int depth,
							 kd_node_t **best, double *best_dist);
						
kd_node_t *nearest_neighbor(kd_node_t *root, int *point, int k);

#endif