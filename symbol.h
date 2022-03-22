#include <string.h>
#include <stdlib.h>

#define SYMBOL_ASSIGN_SIGN ':'
#define DATA_TYPE_DATA ".data"
#define DATA_TYPE_STRING ".string"

char * get_symbol_name(char ** words);

char ** remove_symbol_name(char ** words, char * name);

unsigned int get_symbol_type(char ** words);

unsigned int calculate_symbol_memory_size(char ** words, int type, char * name);
