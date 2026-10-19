//
// Created by user on 19/10/2026.
//

#include "mode_l.h"
#include <stdio.h>
#include <string.h>

int mode_l_run(const char *table_path)
{
    printf("Chargement de la table : %s\n", table_path);

    /* ... chargement de la table ... */

    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0')
            continue;
        printf("Condensat lu : %s\n", line);
        /* ... recherche dans la table ... */
    }

    return 0;
}