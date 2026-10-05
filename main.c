#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

 FILE * file = fopen(argv[1], "r");
printf("the file is supposed to be %s \n", argv[1]);
 if ( file == NULL ) {
        printf( "Cannot open file %s\n", argv[1] );
        exit( 0 );
  
 }
 int count = 0;
 for (char c = getc(file); c != EOF; c = getc(file)){
	 if (c == '\n'){
		count = count + 1;
	 }
 }
    // Close the file
    fclose(file);
    printf("The file has %d lines\n ", count);


 return 0; 

}
