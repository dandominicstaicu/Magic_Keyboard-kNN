#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define COMMAND_LEN 10
#define TRUE 1
#define FALSE 0
#define FILENAME_LEN 50

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);				        \
		}							\
	} while (0)

typedef struct kd_node kd_node;
struct kd_node {
	int *point;
	kd_node *left;
	kd_node *right;
};

typedef struct kd_tree kd_tree;
struct kd_tree {
	int dim;
	kd_node *root;
};

// build the kd tree
kd_tree *create_tree()
{
	kd_tree *tree = (kd_tree *)malloc(sizeof(kd_tree));
	DIE(!tree, "malloc failed for tree in create_tree()");

	tree->dim = 0;
	tree->root = NULL;
	
	return tree;
}

kd_node *create_node(int *point, int k)
{
	kd_node *new_node = (kd_node *)malloc(sizeof(kd_node));
	DIE(!new_node, "malloc failed for new_node in create_node()");

	new_node->point = (int *)malloc(sizeof(int) * k);
	DIE(!new_node->point, "malloc failed for new_node->point in create_node()");

	for (int i = 0; i < k; ++i) {
		new_node->point[i] = point[i];
	}

	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

// insert a node into the kd tree
kd_node *insert_node(kd_node *root, int *point, int k, int depth)
{
	if (!root)
		return create_node(point, k);

	int cd = depth % k;

	if (point[cd] < root->point[cd]) {
		root->left = insert_node(root->left, point, k, depth + 1);
	} else {
		root->right = insert_node(root->right, point, k, depth + 1);
	}

	return root;
}

double distance(int *point1, int *point2, int k)
{
	double dist = 0;

	for (int i = 0; i < k; ++i) {
		double diff = (double)point1[i] - (double)point2[i];
		dist += diff * diff;
	}

	return sqrt(dist);
}

void nearest_neighbor_search(kd_node *root, int *target, int k, int depth, kd_node **best, double *best_dist)
{
	if (!root)
		return;

	double dist = distance(root->point, target, k);
	int cd = depth % k;
	int diff = target[cd] - root->point[cd];

	kd_node *closer_node = diff < 0 ? root->left : root->right;
	kd_node *further_node = diff < 0 ? root->right : root->left;

	nearest_neighbor_search(closer_node, target, k, depth + 1, best, best_dist);

	if (dist < *best_dist) {
		*best = root;
		*best_dist = dist;
	}

	if (abs(diff) < *best_dist) {
		nearest_neighbor_search(further_node, target, k, depth + 1, best, best_dist);
	}

}

// find the nearest neighbor
kd_node *nearest_neighbor(kd_node *root, int *point, int k)
{
	kd_node *best = NULL;
	double best_dist = INFINITY;

	nearest_neighbor_search(root, point, k, 0, &best, &best_dist);

	return best;
}

// free the tree with all its nodes
void free_tree(kd_node *node)
{
	if (node != NULL) {
		free(node->point);

		free_tree(node->left);
		free_tree(node->right);

		free(node);
	}
}

int hash_command(char *command)
{
	if (strcmp(command, "LOAD") == 0)
		return 0;
	else if (strcmp(command, "NN") == 0)
		return 1;
	else if (strcmp(command, "RS") == 0)
		return 2;
	else if (strcmp(command, "EXIT") == 0)
		return 3;

	return -1;
}

// handle the LOAD command
void command_load(kd_tree *tree, int *n, int *k)
{
	char filename[FILENAME_LEN];
	scanf("%s", filename);

	FILE *file = fopen(filename, "rt");
	if (file == NULL) {
		fprintf(stderr, "Could not open file\n");
		return;
	}

	*n = 0;
	*k = 0;

	fscanf(file, "%d %d", n, k);

	// read from the file and insert into the tree
	for (int i = 0; i < *n; ++i) {
		int *point = (int *)malloc(sizeof(int) * *k);
		DIE(!point, "malloc failed for point in command_load()");

		for (int j = 0; j < *k; ++j) {
			fscanf(file, "%d", &point[j]);
		}

		// insert the point into the tree
		tree->root = insert_node(tree->root, point, *k, 0);
		
		free(point);
	}

	fclose(file);
}

// handle the NN command
void command_nn(kd_tree *tree, int k)
{
	int *point = (int *)malloc(sizeof(int) * k);
	DIE(!point, "malloc failed for point in command_nn()");

	for (int i = 0; i < k; ++i) {
		// read input of NN command
		// NN <b_1> <b_2> ... <b_k>
		scanf("%d", &point[i]);
	}

	kd_node *neighbor = nearest_neighbor(tree->root, point, k);

	for (int i = 0; i < k; ++i) {
		printf("%d ", neighbor->point[i]);
	}
	printf("\n");

	free(point);
}

void range_search(kd_node *root, int *start, int *end, int k, int depth)
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
		for (int i = 0; i < k; ++i) {
			printf("%d ", root->point[i]);
		}
		printf("\n");
	}

	if (start[cd] <= root->point[cd]) {
		range_search(root->left, start, end, k, depth + 1);
	}

	if (end[cd] >= root->point[cd]) {
		range_search(root->right, start, end, k, depth + 1);
	}
}

void command_rs(kd_tree *tree, int k)
{
	int *start = (int *)malloc(sizeof(int) * k);
	DIE(!start, "malloc failed for start in command_rs()");

	int *end = (int *)malloc(sizeof(int) * k);
	DIE(!end, "malloc failed for end in command_rs()");

	for (int i = 0; i < k; ++i) {
		// read input of RS command
		// RS <start_1> <end_1> <start_2> <end_2> ... <start_k> <end_k> 
		scanf("%d %d", &start[i], &end[i]);
	}

	range_search(tree->root, start, end, k, 0);

	free(start);
	free(end);
}

void command_exit(kd_tree *tree)
{
	free_tree(tree->root);
	free(tree);
	exit(0);
}

int main(void)
{
	kd_tree *tree = create_tree();

	char command[COMMAND_LEN];
	scanf("%s", command);
	int n = 0, k = 0;

	while (TRUE) {
		switch (hash_command(command))
		{
		case 0:
			command_load(tree, &n, &k);
			break;
		case 1:
			command_nn(tree, k);
			break;
		case 2:
			command_rs(tree, k);
			break;
		case 3:
			command_exit(tree);
			return 0;
		default:
			fprintf(stderr, "Invalid command\n");
			return 2;
		}
		scanf("%s", command);
	}



	command_exit(tree);
	return 0;
}