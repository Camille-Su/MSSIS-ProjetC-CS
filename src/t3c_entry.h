//
// Created by user on 21/10/2026.
//

#ifndef T3C_ENTRY_H
#define T3C_ENTRY_H

#define MAX_WORD_LEN 128
#define HASH_HEX_LEN 32

typedef struct {
    char password[MAX_WORD_LEN];
    char hash[HASH_HEX_LEN + 1];
} t3c_entry;

#endif
