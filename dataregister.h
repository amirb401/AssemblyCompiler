#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_VALUE 0
#define DATA_TYPE_SYMBOL ".data"
#define STRING_TYPE_SYMBOL ".string"

typedef enum {
	NDT, /* not data type */
	STRING_TYPE,
	DATA_TYPE
} DataType;

int calculate_data_space(char ** data);

void data_to_bits(char ** words);

int get_data_counter(int size);

int get_data_memory_amount();
