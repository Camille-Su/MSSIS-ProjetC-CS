#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include "argParser.h"

void parseArgs(char *input[], char *mode, char *path, FILE *inFile, FILE *outFile){
    printf("input[1][0] = %s\n", input[1]);
    if(input[1][0] == 'G') {
        printf("enter if\n");
        *mode = 'G';
        if(input[2] == "-i" ||input[2] == "--input") {
            printf("input[2] =%s\n", input[2]);
            printf("input[3] =%s\n", input[3]);
            inFile = fopen(input[3], "r");

            if ( inFile == NULL ) {
                    printf( "Cannot open file %s\n", input[3] );
                    exit( 0 );
            }
        } else {
            printf("Mauvais argument\n");
        }
        if(input[4] == "-o" ||input[4] == "--output") {
            outFile = fopen(input[5], "w");
        
            if ( inFile == NULL ) {
                    printf( "Cannot open file %s\n", input[5] );
                    exit( 0 );
            }
        } else {
            printf("Mauvais argument\n");
        }
    } else {

    if(input[1] == "L" && (input[1] == "-t" || input[1] == "--table")) {
        mode = "L";
        inFile = fopen(input[3], "r");
        if ( inFile == NULL ) {
                printf( "Cannot open file %s\n", input[3] );
                exit( 0 );
        }
    } else {
            printf(("Mauvaise option\n"));
        }
    }
}