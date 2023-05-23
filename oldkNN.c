#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LEN 5
#define TRUE 1
#define FILENAME_LEN 25

typedef struct node node;
struct node {
	int *point;
	node *left;
	node *right;
};

typedef struct kdtree kdtree;
struct kdtree {
	int dim;
	node *root;
};

kdtree *create_tree(int dim)
{
	kdtree *tree = (kdtree *)malloc(sizeof(kdtree));
	tree->dim = dim;
	tree->root = NULL;

	return tree;
}

node *create_node(int arr[], int k)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->point = (int *)malloc(sizeof(int) * k);

	for (int i = 0; i < k; ++i) {
		new_node->point = arr[i];
	}

	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

node *insert_node(node *root, int point[], unsigned depth, int dim)
{
	if (root == NULL)
		return create_node(point, dim);

	unsigned cd = depth % dim;

	if (point[cd] < (root->point[cd])) {
		root->left = insert_node(root->left, point, depth + 1, dim);
	} else {
		root->right = insert_node(root->right, point, depth + 1, dim);
	}

	return root;
}

void free_node()

void load(kdtree *tree, FILE *file)
{

}

int hash_command(char *command)
{
	if (strcmp(command, "LOAD") == 0)
		return 0;
	else if (strcmp(command, "NN") == 0)
		return 1;
	else if (strcmp(command, "RS") == 0)
		return 2;

	return -1;
}

void command_load()
{
	char filename[FILENAME_LEN];
	scanf("%s", filename);

	FILE *file = fopen(filename, "rt");
	if (file == NULL) {
		// fprintf(stderr, "Could not open file\n");
		return;
	}

	

}

int main(void)
{
	char command[COMMAND_LEN];

	scanf("%s", command);

	while (TRUE) {
		switch (hash_command(command)) {
		case 0:

			break;
		case 1:
			break;
		case 2:
			break;
		}
	}
	return 0;
}
