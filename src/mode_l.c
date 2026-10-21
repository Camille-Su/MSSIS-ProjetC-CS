#include "mode_l.h"
#include "binary_tree.h"
#include "t3c_entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static node_t* load_table (const char *table_path) {
    FILE * input_f = fopen(table_path, "r");
    if ( input_f == NULL ) {
        fwrite("[ERROR] : Cannot open table file!\n", 35, 1, stderr);
       return 0;
    }
    int count = 0;
    t3c_entry entry;

    fscanf(input_f, "%s\t%32s\n", entry.password, entry.hash);

    node_t *t = createNode(entry);

    while (fscanf(input_f, "%s\t%32s\n", entry.password, entry.hash) == 2) {
        node_t *n = findNode(entry, t);
        if (n == NULL) {
            addNode(entry, t);
        } else {
            addToExistingHash(n, entry);
        }
        count++;
    }
    fclose(input_f);
    return t;
}

int mode_l_run(const char *table_path) {
    char line[33];
    char null[5] = "NULL";
    node_t *tree = load_table(table_path);

    fflush(stdin);
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0')
            continue;
        t3c_entry entry;
        strcpy(entry.hash, line);
        strcpy(entry.password, null);
        node_t *n = findNode(entry, tree);
        if (n == NULL) {
            printf("\n");
        } else {
            pass_node_t *passwords = n->passwords;
            pass_node_t *curr = passwords;
            while(curr->next != NULL) {
                printf("%s\t", curr->password);
                curr = curr->next;
            }
            printf("%s\n", curr->password);
        }
    }
    destroyTree(tree);
    return 0;
}