# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpedantic -std=c99 -O0 -g

# define targets
TARGETS=kNN mk 

#define object-files
OBJ=mk.o kNN.o autocomplete.o autocorrect.o trie_commands.o utils_mk.o kNN_commands.o kNN_operations.o nearest_neighbor.o range_search.o utils_kNN.okNN_commands.o kNN_operations.o nearest_neighbor.o range_search.o utils_kNN.o

build: $(TARGETS)

mk: mk.o autocomplete.o autocorrect.o trie_commands.o utils_mk.o
	$(CC) $(CFLAGS) $^ -o $@

kNN: kNN.o kNN_commands.o kNN_operations.o nearest_neighbor.o range_search.o utils_kNN.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_Dan-DominicStaicu_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJ)

.PHONY: pack clean
