#include "utils_kNN.h"

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
