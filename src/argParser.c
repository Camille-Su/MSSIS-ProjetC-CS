#include <stdio.h>
#include <stdlib.h>

void parseArgs(char* input[], char *mode, char *path, FILE *inFile, FILE *outFile){
    if(input[1] == "G") {
        *mode = "G";
        if(input[2] == "-i" ||input[2] == "--input") {
            
            inFile = fopen(input[3], "r");

            if ( inFile == NULL ) {
                    printf( "Cannot open file %s\n", input[3] );
                    exit( 0 );
            }
        } else {
            printf("Mauvais argument\n");
        }
        if(input[4] == "-o" ||input[4] == "--output") {
            outFile = fopen(input[5], "r");
        
            if ( inFile == NULL ) {
                    printf( "Cannot open file %s\n", input[5] );
                    exit( 0 );
            }
        } else {
            printf("Mauvais argument\n");
        }
    }
}