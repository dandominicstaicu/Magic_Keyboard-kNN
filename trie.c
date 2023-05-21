

TrieNode *get_node() {
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = 0;
    newNode->frequency = 0;
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    
    return newNode;
}

void insert(TrieNode *root, const char *word) {
    int length = strlen(word);
    int index;

    TrieNode *node = root;
    
    for (int level = 0; level < length; level++) {
        index = word[level] - 'a';
        if (!node->children[index])
            node->children[index] = getNode();

        node = node->children[index];
    }

    node->isEndOfWord = 1;
    node->frequency++;
}