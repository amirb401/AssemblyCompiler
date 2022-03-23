#include <stdbool.h>
#include <string.h>

#define WORD_SPLIT_TOKENS " ,\t"
#define EXTERNAL_SIGN ".extern"
#define ENTRY_SIGN ".entry"
#define DATA_SIGN ".data"
#define STRING_SIGN ".string"

#define EXTERNAL_SYMBOL_TABLE_VALUE 0


void first_loop_process(char *line);

void second_loop_process(char *line);

void update_data_symbols_addresses();

void reset_counters();

void set_saved_memory_cells(int instructions, int data);
