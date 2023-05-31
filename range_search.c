#include "range_search.h"

void range_search(kd_node_t *root, int *start, int *end, int k, int depth)
{
	if (!root)
		return;

	int cd = depth % k;

	int in_range = TRUE;
	for (int i = 0; i < k; ++i) {
		if (root->point[i] < start[i] || root->point[i] > end[i]) {
			in_range = FALSE;
			break;
		}
	}

	if (in_range) {
		for (int i = 0; i < k; ++i)
			printf("%d ", root->point[i]);
		printf("\n");
	}

	if (root->left && start[cd] <= root->point[cd])
		range_search(root->left, start, end, k, depth + 1);

	if (root->right && end[cd] >= root->point[cd])
		range_search(root->right, start, end, k, depth + 1);
}
