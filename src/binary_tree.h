//
// Created by user on 21/10/2026.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "t3c_entry.h"

typedef struct pass_node {
    char *password;
    struct pass_node *next;
}pass_node_t;

typedef struct node {
    char *hash;
    pass_node_t *passwords;
    struct node *a;
    struct node *b;
}node_t;

node_t *createNode(t3c_entry entry);
node_t* findNode(t3c_entry entry, node_t* tree);
void addNode(t3c_entry entry, node_t *t);
void addToExistingHash(node_t *tree, t3c_entry entry);
void destroyTree(node_t *n);

#endif //BINARY_TREE_H
