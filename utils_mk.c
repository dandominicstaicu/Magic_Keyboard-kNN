#include "utils_mk.h"

int hash_command(char *command)
{
	if (strcmp(command, "INSERT") == 0)
		return 0;
	else if (strcmp(command, "LOAD") == 0)
		return 1;
	else if (strcmp(command, "REMOVE") == 0)
		return 2;
	else if (strcmp(command, "AUTOCORRECT") == 0)
		return 3;
	else if (strcmp(command, "AUTOCOMPLETE") == 0)
		return 4;
	else if (strcmp(command, "EXIT") == 0)
		return 5;

	return -1;
}
