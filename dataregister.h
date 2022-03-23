#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_VALUE 0
#define DATA_TYPE_SYMBOL ".data"
#define STRING_TYPE_SYMBOL ".string"
#define ENT_TYPE_SYMBOL ".entry"
#define EXT_TYPE_SYMBOL ".external"

typedef enum DataType {
	ND_T, /* no data type */
	DAT_TYPE,
	STRIN_TYPE,
	ENT_TYPE,
	EXT_TYPE
} DataType;


int calculate_data_space(char ** data);

void data_to_bits(char ** words);

int get_data_counter(int size);

int get_data_memory_amount();
