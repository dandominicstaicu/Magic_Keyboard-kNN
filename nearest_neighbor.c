#include "kNN_operations.h"

// calculate the distance between two points
double distance(int *point1, int *point2, int k)
{
	double dist = 0;

	for (int i = 0; i < k; ++i) {
		// calculate the difference between the two points
		double diff = (double)point1[i] - (double)point2[i];
		// add the square of the difference to the distance
		dist += diff * diff;
	}

	// return the square root of the distance
	return sqrt(dist);
}

void nearest_neighbor_search(kd_node_t *root, int *target, int k, int depth,
							 kd_node_t **best, double *best_dist)
{
	if (!root)
		return;

	// calculate the distance between the current node and the target
	double dist = distance(root->point, target, k);
	// calculate the current distance
	int cd = depth % k;
	// calculate the difference between the current node and the target
	int diff = target[cd] - root->point[cd];

	kd_node_t *closer_node = diff < 0 ? root->left : root->right;
	kd_node_t *further_node = diff < 0 ? root->right : root->left;

	// search the subtree that is closer to the target
	nearest_neighbor_search(closer_node, target, k, depth + 1, best, best_dist);

	// update the best distance and the best node
	if (dist < *best_dist) {
		*best_dist = dist;
		*best = root;
	}

	// if the dist between the current and the target is less than the best dist
	if (abs(diff) < *best_dist) {
		// search the subtree that is further from the target
		nearest_neighbor_search(further_node, target, k, depth + 1,
								best, best_dist);
		if (dist < *best_dist) {
			*best_dist = dist;
			*best = root;
		}
	}
}

// find the nearest neighbor
kd_node_t *nearest_neighbor(kd_node_t *root, int *point, int k)
{
	kd_node_t *best = NULL; // set the best node to NULL
	double best_dist = INFINITY; // set the best distance to infinity

	nearest_neighbor_search(root, point, k, 0, &best, &best_dist);

	return best;
}
