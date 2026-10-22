#include "binary_tree.h"
#include <stdio.h>
#include "t3c_entry.h"
#include <stdlib.h>
#include <string.h>

static char *dup_str(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy) memcpy(copy, s, len);
    return copy;
}

pass_node_t *createPassNode(char *password) {
    pass_node_t *passNode= malloc(sizeof(pass_node_t));
    passNode->password = dup_str(password);
    passNode->next = NULL;
    return passNode;
}

node_t *createNode(t3c_entry entry) {
    node_t* node = malloc(sizeof(node_t));
    node->a = NULL;
    node->b = NULL;
    node->hash = dup_str(entry.hash);
    node->passwords = createPassNode(entry.password);
    return node;
}


node_t *getNext(t3c_entry entry, node_t *n) {
    int cmp = strcmp(entry.hash, n->hash);
    if (cmp > 0) {
        return n->a;
    }
    if (cmp < 0) {
        return n->b;
    }
    return NULL;
}

void addNode(t3c_entry entry, node_t *t) {
    node_t *curr = t;
    node_t *prev = NULL;
    while (curr != NULL) {
        prev = curr;
        curr = getNext(entry, curr);
    }
    if (strcmp(entry.hash, prev->hash) == 0) {
        addToExistingHash(prev, entry);
        return;
    }
    node_t *new_node = createNode(entry);
    if (strcmp(entry.hash, prev->hash) > 0) {
        prev->a = new_node;
    } else {
        if (strcmp(entry.hash, prev->hash) < 0) {
            prev->b = new_node;
        }
    }
}

node_t *findNode(t3c_entry entry, node_t* tree) {
    node_t *found = NULL;
    node_t *curr = tree;
    while(curr != NULL) {
        if(strcmp(entry.hash, curr->hash) == 0) {

            found = curr;
            break;
        }
        curr = getNext(entry,curr);
    }

    return found;
}

void addToExistingHash(node_t *tree, t3c_entry entry) {;
    node_t *node = findNode(entry, tree);
    pass_node_t *curr = node->passwords;;

    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = createPassNode(entry.password);

}

static void destroyPasswords(pass_node_t *passwords) {
    pass_node_t *curr = passwords;
    while(curr->next != NULL)      {
        pass_node_t *next = curr->next;
        free(curr->password);
        free(curr);
        curr = next;
    }
    free(curr->password);
    free(curr);
}

void destroyTree(node_t *n) {
    if (n == NULL) {
        return;
    }
    node_t *a = n->a;
    node_t *b = n->b;
    destroyPasswords(n->passwords);
    free(n->hash);
    free(n->passwords);
    free(n);
    destroyTree(a);
    destroyTree(b);
}