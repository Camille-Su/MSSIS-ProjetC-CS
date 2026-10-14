#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <assert.h>
//#include<argParser.h>
#include <argp.h>



struct arguments {
    char *args[2];                
    char *mode;                  
    char *output_file;
    char *input_file;            
};

static int parse_opt (int key, char *arg,struct argp_state *state){
   struct arguments *arguments = state->input;

   switch (key)
   {
      case 'i': 
         printf ("i\n"); 
         arguments->input_file;
         break;
      case 'o': 
         printf ("o\n"); 
         break;
      case 't': 
         printf ("t\n"); 
         break;
         
      case ARGP_KEY_ARG:
         printf("entré dans case key arg %s\n", arg);
         if (state->arg_num == 1){
            /* First argument */
            arguments->mode = arg;
         }
         printf("sorti\n");
         printf("Le mode est : %s\n", arguments->mode);
         break;
         
      case ARGP_KEY_END:
         printf("\n");
         break;
   }
   return 0;
}




int main(int argc, char *argv[]) {
   static char doc[] = "Hashcat CLI program";
   static char args_doc[] = "./t3c G -i <dictionnaire> -o <t3c_output> [-a <algo>]|| ou ||  ./t3c L -t <t3c_path>";

   

   struct argp_option options[] = {
      {"input", 'i', "IN_FILE", OPTION_ARG_OPTIONAL, "Input dictionnary file"},
      {"output",  'o', "OUT_FILE", OPTION_ARG_OPTIONAL, "Output to OUT_FILE"},
      {"algo",  'a', "ALGO", OPTION_ARG_OPTIONAL, "Algorithm to use, MD5 by default"},
      {"table",  't', "TABLE_FILE",OPTION_ARG_OPTIONAL, "path to table FILE "},
      { 0 }
   };


   FILE *inFile = NULL;
   FILE *outFile = NULL;
   
   //char *path = (char *) malloc(254 * sizeof(char));
   //char mode;

   //parseArgs(argv, &mode, path, inFile, outFile);
/*

   if(argv[1] != NULL) {
      //path = argv[1];
      strcpy( path, argv[1] );
   } else {
      path = "test.txt";
   }

   FILE * file = fopen(path, "r");

   if ( file == NULL ) {
         printf( "Cannot open file %s\n", path );
         exit( 0 );
   }

   free(path);
   int count = 0;
   char *a = (char *) malloc(254 * sizeof(char));
   int c = fscanf(file, "%s\n", a); //renvoie nbr d'arguments scannés, donc si pas 1, on est à la fin

   while (c == 1) {
      count++;
      printf("%s\n", a);
      c = fscanf(file, "%s\n", a);
   }
   free(a);

   // Close the file
   fclose(file);
   printf("The file has %d lines\n ", count);
   
   printf("path = %s \n", path);
   printf("mode = %c \n", mode);
   free(path);

   fclose(inFile);
   fclose(outFile);
   printf("mode = %c\n", mode);
   */

   struct argp argp = { options, parse_opt };



   return argp_parse (&argp, argc, argv, 0, 0, 0);

   

}
