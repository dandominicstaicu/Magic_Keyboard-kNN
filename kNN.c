#include "utils_kNN.h"
#include "kNN_commands.h"

int main(void)
{
	kd_tree *tree = create_tree();

	char command[COMMAND_LEN];
	scanf("%s", command);
	int n = 0, k = 0;

	while (TRUE) {
		switch (hash_command(command)) {
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
