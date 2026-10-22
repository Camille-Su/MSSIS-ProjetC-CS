#include "mode_g.h"

#include <ctype.h>

#include "t3c_entry.h"
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define HASH_HEX_LEN 128 //longueur de hash max: sha512
#define MAX_WORD_LEN 128    //arbitraire

static int write_entry(FILE *output, const char *password, const char *hash_hex) {
    if (fprintf(output, "%s\t%s\n", password, hash_hex) < 0)
        return 1;
    return 0;
}

int get_hash_hex (char *password, char *hash_hex, const EVP_MD *md) {
    unsigned char digest[EVP_MAX_MD_SIZE];  //contient le digest
    unsigned int digest_len = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ctx) { ///creation de pointeur n'a pas fonctionné
        return 1;
    }
    if (EVP_DigestInit_ex(ctx, md, NULL) != 1 ||
       EVP_DigestUpdate(ctx, password, strlen(password)) != 1 ||
       EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) { //echec à l'init, update ou finalisation
       EVP_MD_CTX_free(ctx);
       return 1;
    }
    EVP_MD_CTX_free(ctx);

    for (unsigned int i = 0; i < digest_len; i++) {
        sprintf(hash_hex + (i * 2), "%02x", digest[i]); //ecriture sur 2o pour avoir string
    }
    hash_hex[digest_len * 2] = '\0';
    return 0;
}
/** Retourne :
 * 1 si password lu normalement
 * -1 si password tronqué (>127 char)
 * 0 si EOF
 * */
int read_password(FILE *input_f, char *buffer, size_t len) {
    int ch;
    do {
        ch = fgetc(input_f);
    } while (ch != EOF && isspace(ch));
    if (ch == EOF)
        return 0;

    size_t i = 0;
    int trunc = 0;

    while (ch != EOF && !isspace(ch)) {
        if (i < len - 1) {
            buffer[i++] = (char)ch;
        } else {
            trunc= 1; // on continue à lire pour vider le buffer
        }
        ch = fgetc(input_f);
    }
    buffer[i] = '\0';
    if (trunc) { return -1;}
    return 1;
}

const EVP_MD *get_md_algo(const char *algo_name)
{
    if (strcmp(algo_name, "md5") == 0)
        return EVP_md5();
    if (strcmp(algo_name, "sha256") == 0)
        return EVP_sha256();
    if (strcmp(algo_name, "sha1") == 0)
        return EVP_sha1();
    if (strcmp(algo_name, "sha512") == 0)
        return EVP_sha512();
    return NULL; /* algo inconnu */
}


int mode_g_run(const char *input, const char *output, const char *algo) {

    FILE * input_f = fopen(input, "r");



    if ( input_f == NULL ) {
        fwrite("[ERROR] : Cannot open input file!\n", 35, 1, stderr);
        return( 1 );
    }
    FILE * output_f = fopen(output, "w");

    if ( output_f == NULL ) {
        fwrite("[ERROR] : Cannot open output file!\n", 36, 1, stderr);
        return( 1 );
    }
    const EVP_MD *md = (algo == NULL)? EVP_md5() : get_md_algo(algo);

    if (md == NULL) {
        fprintf(stderr, "[ERROR] : algorithme inconnu '%s'\n", algo);
        fclose(input_f);
        fclose(output_f);
    }

    t3c_entry entry;
    int c;

    while ((c = read_password(input_f, entry.password, sizeof(entry.password))) != 0 ) {

        if ( c== -1 ) {
            fprintf(stderr, "[ERROR] : Password too long, ignored '%s'\n", entry.password);
            continue;
        }

        if (get_hash_hex(entry.password, entry.hash, md) != 0) {
            fprintf(stderr, "[ERROR] : hash failed for '%s'\n", entry.password);
            continue;
        }
        write_entry(output_f, entry.password, entry.hash);
    }
    fclose(input_f);
    fclose(output_f);
    return 0;
}