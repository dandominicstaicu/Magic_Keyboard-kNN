#include "kNN_commands.h"

// handle the LOAD command
void command_load(kd_tree *tree, int *n, int *k)
{
	char filename[FILENAME_LEN];
	scanf("%s", filename);

	FILE *file = fopen(filename, "rt");
	DIE(!file, "fopen failed for file in command_load()");

	*n = 0;
	*k = 0;

	fscanf(file, "%d %d", n, k);

	int *point = (int *)malloc(sizeof(int) * (*k));
	DIE(!point, "malloc failed for point in command_load()");

	// read from the file and insert into the tree
	for (int i = 0; i < *n; ++i) {
		for (int j = 0; j < *k; ++j)
			fscanf(file, "%d", &point[j]);

		// insert the point into the tree
		tree->root = insert_node(tree->root, point, *k, 0);
	}

	free(point);
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

	kd_node_t *neighbor = nearest_neighbor(tree->root, point, k);

	for (int i = 0; i < k; ++i)
		printf("%d ", neighbor->point[i]);
	printf("\n");

	free(point);
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
