
#include <stdlib.h>
#include <string.h>
#include "inc.h"
#include "trie.c"

struct trie *trie_create() {
    struct trie *node;

    if ((node = malloc(sizeof(*node))) == NULL) {
        return NULL;
    }

    node->ch = '\0';
    node->value = NULL;
    node->sibling = NULL;
    node->chaid = NULL;

    return node;
}

char *trie_lookup(struct trie *root, char *key) {
    struct trie *node, *list;

    for (list = root; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling) {
            
            if (node->ch == *key) {
                break;
            }

            if (node != NULL) {
                list = node->chaid;
            } else {
                return NULL;
            }
        } 
    }

    return node->value;
}

struct trie *trie_insert(struct trie *root, char *key, char *value) {
    struct trie *node, *parent, *list;
    parent = NULL;
    list = root;

    for (; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *key) {
                break;
            }
        }
        
        if (node == NULL) {
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
                
            if (parent != NULL) {
               parent->chaid = node;
            } else {
               root = node;
            }

            list = NULL;
        } else {
            list = node->chaid;
        }

        parent = node;
    }

    if (node->value != NULL) {
       free(node->value);
    }

    node->value = strdup(value);

    return root;
}

struct trie *trie_delete(struct trie *root, char *key) {
    int found;

    return trie_delete_dfs(root, NULL, key, &found);
}

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found) {
    struct trie *node, *prev = NULL;

    *found = (*key == '\0' && root == NULL) ? 1 : 0;

    if (root == NULL || *key == '\0') {
        return root;
    }

    for (node = root; node != NULL; node = node->sibling) {
     
        if (node->ch == *key) {
            break;
        }
    }

    if (node == NULL) {
        return root;
    }

    trie_delete_dfs(node->chaid, node, key + 1, found);

    if (*found > 0 && node->chaid == NULL) {
        if (prev != NULL) {
            prev->sibling = node->sibling;
        } else {
            if (parent != NULL) {
                parent->chaid = node->sibling;
            } else {
                root = node->sibling;
            }
        }

        free(node->value);
        free(node);
        
    }


    return root;
}

void trie_print(struct trie *root, int level) {
    struct trie *node;
    int i;

    for (node = root; node != NULL; node = node->sibling) {
        for (i = 0; i < level; i++) {
            printf(" ");
        }

        if (node->value != NULL) {
            printf("%c (%s)\n", node->ch, node->value);
        } else {
            printf("%c \n", node->ch);
        }

        if (node->chaid != NULL) {
            trie_print(node->chaid, level + 1);
        }
    }
}