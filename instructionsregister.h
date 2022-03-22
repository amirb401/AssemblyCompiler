#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define IC_DEFAULT_VALUE 100
#define MAX_REGISTERS 16
#define IMMEDIATE_SYMBOL '#'

/* type of addressing mode */
typedef enum addressingMode {
	NAM = -1, /* not an address mode */
	IMMEDIATE = 0,
	DIRECT = 1,
	INDEXED = 2,
	REGISTER = 3
} AddressingMode;

/* command struct */
typedef struct {
	unsigned id;
	char * name;
	AddressingMode * allowedAddressingsSrc;
	AddressingMode * allowedAddressingsDest;
}  Command;

signed int get_command_id(char * command);

bool is_command(char * command);

int calculate_command_space(char ** commandline);

int get_instructions_counter(int size);

int get_instructions_memory_amount();

void instruction_to_bits(char ** words);
