#include "utils_mk.h"
#include "trie_commands.h"
#include "autocomplete.h"
#include "autocorrect.h"

int main(void)
{
	trie_t *root = malloc(sizeof(trie_t));
	DIE(!root, "malloc failed in main\n");

	root->is_end_of_word = 0;
	root->freq = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		root->subtrie[i] = NULL;

	char command[COMMAND_LEN];
	scanf("%s", command);

	while (TRUE) {
		switch (hash_command(command)) {
		case 0:
			command_insert(root);
			break;
		case 1:
			command_load(root);
			break;
		case 2:
			command_remove(root);
			break;
		case 3:
			command_autocorrect(root);
			break;
		case 4:
			command_autocomplete(root);
			break;
		case 5:
			command_exit(root);
			return 0;
		default:
			// fprintf(stderr, "Invalid command\n");
			break;
		}

		scanf("%s", command);
	}

	command_exit(root);
	return 0;
}
