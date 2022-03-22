#include <stdbool.h>
#include <string.h>

#define WORD_SPLIT_TOKENS " ,\n\t"
#define EXTERNAL_SIGN ".extern"
#define ENTRY_SIGN ".entry"
#define MACRO_SIGN ".define"
#define EXTERNAL_ADDRESS_VALUE 0


void first_loop_process(char *line);

void second_loop_process(char *line);

void update_data_symbols_addresses();

void reset_counters();

void set_saved_memory_cells(int instructions, int data);
