
/**
* Create empty trie struct
*/
struct trie *trie_create();

/**
* Search key in the trie
*/
char *trie_lookup(struct trie *root, char *key);

/**
* Insert new node as value in trie
*/
struct trie *trie_insert(struct trie *root, char *key, char *value);

/**
* Remove node by key from trie
*/
struct trie *trie_delete(struct trie *root, char *key);

/**
* Remove and reconnection nodes
*/
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found);

/**
 * Support function print all nodes before was created
 */
void trie_print(struct trie *root, int level);