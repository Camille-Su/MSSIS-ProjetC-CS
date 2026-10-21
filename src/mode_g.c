#include "mode_g.h"
#include "t3c_entry.h"
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define HASH_HEX_LEN 32 //longueur d'un hash MD5
#define MAX_WORD_LEN 128    //arbitraire

static int write_entry(FILE *output, const char *password, const char *hash_hex) {
    if (fprintf(output, "%s\t%s\n", password, hash_hex) < 0)
        return 1;
    return 0;
}

int get_MD5_hex (char *password, char *hash_hex) {
    unsigned char digest[EVP_MAX_MD_SIZE];  //contient le digest MD5
    unsigned int digest_len = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ctx) { ///creation de pointeur n'a pas fonctionné
        return 1;
    }
    if (EVP_DigestInit_ex(ctx, EVP_md5(), NULL) != 1 ||
       EVP_DigestUpdate(ctx, password, strlen(password)) != 1 ||
       EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) { //echec à l'init, update ou finalisation

        EVP_MD_CTX_free(ctx);
        return 1;
    }
    EVP_MD_CTX_free(ctx);

    for (int i = 0; i < digest_len; i++) {
        sprintf(hash_hex + (i * 2), "%02x", digest[i]); //ecriture sur 2o pour avoir string
    }
    hash_hex[digest_len * 2] = '\0';
    return 0;
}

int mode_g_run(const char *input, const char *output, const char *algo)
{
    printf("Génération : input=%s output=%s algo=%s\n", input, output, algo);

    FILE * input_f = fopen(input, "r");

    if ( input_f == NULL ) {
        fwrite("[ERROR] : Cannot open input file!\n", 35, 1, stderr);
        exit( 0 );
    }
    FILE * output_f = fopen(output, "w");

    if ( output_f == NULL ) {
        fwrite("[ERROR] : Cannot open output file!\n", 36, 1, stderr);
        exit( 0 );
    }

    int count = 0;
    t3c_entry entry;
    int c = fscanf(input_f, "%127s", entry.password); //renvoie nbr d'arguments scannés, donc si pas 1, on est à la fin
    while (c == 1) {
        if (get_MD5_hex(entry.password, entry.hash) != 0) {
            fprintf(stderr, "[ERROR] : hash failed for '%s'\n", entry.password);
            c = fscanf(input_f, "%127s", entry.password);
            continue;
        } else {
            write_entry(output_f, entry.password, entry.hash);
            count++;
        }
        printf("%s\n", entry.password);
        c = fscanf(input_f, "%s", entry.password);
    }

    fclose(input_f);
    fclose(output_f);
    printf("The file has %d lines\n ", count);

    return 0;
}