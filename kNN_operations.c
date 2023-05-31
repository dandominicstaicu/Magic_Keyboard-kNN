#include "kNN_operations.h"

// build the kd tree
kd_tree *create_tree(void)
{
	kd_tree *tree = (kd_tree *)malloc(sizeof(kd_tree));
	DIE(!tree, "malloc failed for tree in create_tree()");

	tree->root = NULL;

	return tree;
}

// create a node for the kd tree
kd_node_t *create_node(int *point, int k)
{
	// allocate memory for the new node
	kd_node_t *new_node = (kd_node_t *)malloc(sizeof(kd_node_t));
	DIE(!new_node, "malloc failed for new_node in create_node()");

	// allocate memory for the point array
	new_node->point = (int *)malloc(sizeof(int) * k);
	DIE(!new_node->point, "malloc failed for new_node->point in create_node()");

	// Copy the elements from the point array
	for (int i = 0; i < k; ++i)
		new_node->point[i] = point[i];

	// set the left and right children to NULL
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

// insert a node into the kd tree
kd_node_t *insert_node(kd_node_t *root, int *point, int k, int depth)
{
	if (!root)
		return create_node(point, k);

	// calculate the current dimension
	int cd = depth % k;

	// insert into the left subtree if the current point is less than the root
	if (point[cd] < root->point[cd]) {
		root->left = insert_node(root->left, point, k, depth + 1);
	} else {
		// insert into the right subtree if the current is greater than the root
		root->right = insert_node(root->right, point, k, depth + 1);
	}

	return root;
}

// free the tree with all its nodes
void free_tree(kd_node_t *node)
{
	if (node) {
		free_tree(node->left); // free the left subtree
		free_tree(node->right); // free the right subtree

		free(node->point); // free the point array
		free(node); // free the node
	}
}
