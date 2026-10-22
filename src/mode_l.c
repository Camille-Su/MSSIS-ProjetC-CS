#include "mode_l.h"
#include "binary_tree.h"
#include "t3c_entry.h"
#include <stdio.h>
#include <string.h>


static node_t* load_table (const char *table_path) {

    FILE * input_f = fopen(table_path, "r");

    if ( input_f == NULL ) {
       fwrite("[ERROR] : Cannot open table file!\n", 35, 1, stderr);
       return NULL;
    }

    t3c_entry entry;
    if (fscanf(input_f, "%128s\t%128s\n", entry.password, entry.hash) != 2) {
        fprintf(stderr, "[ERROR] : table file is empty or malformed\n");
        fclose(input_f);
        return NULL;
    }

    node_t *t = createNode(entry);
    if (t == NULL) {
        fprintf(stderr, "[ERROR] : could not load table, aborting\n");
        return NULL;
    }
    int c;
    while ((c=fscanf(input_f, "%128s\t%128s\n", entry.password, entry.hash)) == 2) {

        node_t *n = findNode(entry, t);

        if (n == NULL) {
            addNode(entry, t);
        } else {
            addToExistingHash(n, entry);
        }
    }

    fclose(input_f);

    return t;
}

int mode_l_run(const char *table_path) {
    char line[129];
    char null[5] = "NULL";

    node_t *tree = load_table(table_path);
    if (tree == NULL) {
        fprintf(stderr, "[ERROR] : could not load table, aborting\n");
        return 1;
    }

    fflush(stdin);
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0')
            continue;

        if (strcmp(line, "exit") == 0) {
            break;
        }

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