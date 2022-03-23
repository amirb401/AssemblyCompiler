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

/* type of funct  */
typedef enum funct {
	/* relates to opcode 2 */
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,

	/* relates to opcode 5 */
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,

	/* relates to opcode 9 */
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12,

	/* NA anat */
	NA_FUNCT = 0

} funct;

/* command struct */
typedef struct {
	unsigned id;
	char * name;
	funct * reqFunct;
	AddressingMode * allowedAddressingsSrc;
	AddressingMode * allowedAddressingsDest;
}  Command;



signed int get_command_id(char * command);

bool is_command(char * command);

int calculate_command_space(char ** commandline);

int get_instructions_counter(int size);

int get_instructions_memory_amount();

void instruction_to_bits(char ** words);
