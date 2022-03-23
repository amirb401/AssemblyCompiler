#include <string.h>
#include <stdlib.h>

#define SYMBOL_ASSIGN_SIGN ':'
#define DATA_TYPE_DATA ".data" /* the params are array of whole number / numbers (negative and positive) */
#define DATA_TYPE_STRING ".string" /* only one param and its legal string "abc" */
#define DATA_TYPE_ENTRY ".entry" /* only one param and its the label name */
#define DATA_TYPE_EXTERN ".extern" /* only one param and its the undefined label name  */

char * get_symbol_name(char ** words);

char ** remove_symbol_name(char ** words, char * name);

unsigned int get_symbol_type(char ** words);

unsigned int calculate_symbol_memory_size(char ** words, int type, char * name);
