#include <stdio.h>
#include <string.h>
#include <argp.h>
#include "mode_g.h"
#include "mode_l.h"

typedef enum { MODE_NONE, MODE_G, MODE_L } t3c_mode;

typedef struct arguments {
   t3c_mode mode;
   int mode_set;
   char *output_file;
   char *input_file;
   char *table_file;
   char *algo;
}arguments_t;

static struct argp_option options[] = {
   {"input", 'i', "IN_FILE", 0, "Input dictionnary file (mode G, mandatory)"},
   {"output",  'o', "OUT_FILE", 0, "Output to OUT_FILE (mode G, mandatory)"},
   {"algo",  'a', "ALGO", 0, "Algorithm to use {md5, sha1, sha256, sha512}, MD5 by default (mode G, def=md5)"},
   {"table",  't', "TABLE_FILE",0, "path to table FILE (mode L, mandatory)"},
   { 0 }
};

static int parse_opt (int key, char *arg,struct argp_state *state){
   arguments_t *arguments = state->input;

   switch (key){
      case 'i':
         arguments->input_file = arg;
         break;
      case 'o':
         arguments->output_file = arg;
         break;
      case 't':
         arguments->table_file = arg;
         break;
      case 'a':
         arguments->algo = arg;
      break;
         
      case ARGP_KEY_ARG:
         if (arguments->mode_set)
         {
            argp_error(state, "Invalid positional argument : %s\n", arg);
         }
         if ((strcmp(arg, "G") == 0)){
            arguments->mode = MODE_G;
         } else if (strcmp(arg, "L") == 0) {
            arguments->mode = MODE_L;
         } else {
            argp_error(state, "Invalid mode '%s' (expected : G or L)", arg);
         }
         arguments->mode_set = 1;
         break;
         
      case ARGP_KEY_END:
         if (!arguments->mode_set) {
            argp_error(state, "Mode missing (expected : G or L)");
         }
         if (arguments->mode == MODE_G) {
            if (!arguments->input_file)
               argp_error(state, "mode G : -i/--input is mandatory");
            if (!arguments->output_file)
               argp_error(state, "mode G : -o/--output is mandatory");
            if (!arguments->algo)
               arguments->algo = "md5"; /* valeur par défaut */
         } else if (arguments->mode == MODE_L) {
            if (!arguments->table_file)
               argp_error(state, "mode L : -t/--table is mandatory");
         }
         break;
      default:
         return ARGP_ERR_UNKNOWN;
   }
   return 0;
}


int main(int argc, char *argv[]) {
   static char doc[] = "Hashcat CLI program";
   static char args_doc[] = "./t3c G -i <dictionnaire> -o <t3c_output> [-a <algo>]|| ou ||  ./t3c L -t <t3c_path>";

  
   arguments_t arguments= {0};

   arguments.mode = MODE_NONE;

   struct argp argp = { options, parse_opt };
   argp_parse (&argp, argc, argv, 0, 0, &arguments);

   if (arguments.mode == MODE_G) {
      return mode_g_run(arguments.input_file, arguments.output_file, arguments.algo);
   }
   else {
      return mode_l_run(arguments.table_file);
   }

}
