#include "instructionsregister.h"
#include "output.h"

int _IC = IC_DEFAULT_VALUE;

/* 0,1,2,3 */
AddressingMode allAddressModes[] = {IMMEDIATE, DIRECT, INDEXED, REGISTER};
/* 1,2,3 */
AddressingMode noImmediateAddressModes[] = {DIRECT, INDEXED, REGISTER};
/* 1,2 */
AddressingMode drctAndIndxAddressModes[] = {DIRECT, INDEXED};

/* related to opcode 2 */
funct opcode2add[] = {ADD_FUNCT};
funct opcode2sub[] = {SUB_FUNCT};
/* related to opcode 5 */
funct opcode5[] = {CLR_FUNCT, NOT_FUNCT, INC_FUNCT, DEC_FUNCT};
/* related to opcode 9 */
funct opcode9[] = {JMP_FUNCT, BNE_FUNCT, JSR_FUNCT};


/**
* Collection of all the commands,
* with their allowed addressing modes
* for source operand and destination operand
* as mentioned in assignment notebook.
*/
Command command_list[16] = {
	{
		0,
		"mov",
		NULL,
		allAddressModes,
		noImmediateAddressModes
	},
	{
		1,
		"cmp",
		NULL,
		allAddressModes,
		allAddressModes
	},
	{
		2,
		"add",
		opcode2add,
		allAddressModes,
		noImmediateAddressModes
	},
	{
		2,
		"sub",
		opcode2sub,
		allAddressModes,
		noImmediateAddressModes
	},
	{
		4,
		"lea",
		NULL,
		drctAndIndxAddressModes,
		noImmediateAddressModes
	},
	{
		5,
		"clr",
		opcode5, /* CLR_FUNCT */
		NULL,
		noImmediateAddressModes
	},
	{
		5,
		"not",
		opcode5, /* NOT_FUNCT */
		NULL,
		noImmediateAddressModes
	},
	{
		5,
		"inc",
		opcode5, /* INC_FUNCT */
		NULL,
		noImmediateAddressModes
	},
	{
		5,
		"dec",
		opcode5, /* DEC_FUNCT */
		NULL,
		noImmediateAddressModes
	},
	{
		9,
		"jmp",
		opcode9, /* JMP_FUNCT */
		NULL,
		drctAndIndxAddressModes
	},
	{
		9,
		"bne",
		opcode9, /* BNE_FUNCT */
		NULL,
		drctAndIndxAddressModes
	},
	{
		9,
		"jsr",
		opcode9, /* JSR_FUNCT */
		NULL,
		drctAndIndxAddressModes
	},
	{
		12,
		"red",
		NULL,
		NULL,
		noImmediateAddressModes
	},
	{
		13,
		"prn",
		NULL,
		NULL,
		allAddressModes
	},
	{
		14,
		"rts",
		NULL,
		NULL,
		NULL
	},
	{
		15,
		"stop",
		NULL,
		NULL,
		NULL
	}
};

extern int get_file_line();

extern void set_error_mode();

extern bool is_symbol_external(char * name);

extern bool is_symbol_in_list(char * name);

extern int get_symbol_value_by_name(char * name);

bool validate_command(char ** commandline);

bool validate_command_addressing_mode(char * name, AddressingMode dest, AddressingMode src);

AddressingMode addressing_mode_type(char * operand);

bool is_registor_name(char * operand);

bool is_valid_registor(char * operand);

Command get_command_by_name(char * name);

bool is_empty_command_operand_dest(Command command);

bool is_empty_command_operand_src(Command command);

bool is_empty_operands_command(Command command);

bool is_empty_addressing_mode(AddressingMode addressing_mode);

bool is_addressing_mode_allowed_by_command(AddressingMode addressing_mode, AddressingMode * command_allowed);

int calculate_space_by_addressing_modes(AddressingMode dest, AddressingMode src);

int calculate_space_by_addressing_mode(AddressingMode);

int calculate_number_of_operands(char ** commandline, char * commandName);

char * get_array_name(char * name);

char * get_array_i_value(char * array);

MachineCode get_operand_mchine_code(char * op);

int get_absolute_value(char * str);

void add_to_external_list(char * name, int line);

void create_lines(int commandCode, int srcAddressMode, int destAddressMode);

void create_operand_lines(char * src, char * dest);

void create_single_line_for_registers(char * src, char * dest);

void create_operand_line(char * op, AddressingMode am);

void create_array_lines(char * op);

void build_op_line(int value, MachineCode mc);

signed int get_command_id(char * command)
{
	int count = 16;

	while(count--) {
		if(strcmp(command_list[count].name, command) == 0) {
			return command_list[count].id;
		}
	}
	return -1;
}

Command get_command_by_name(char * name)
{
	int id = get_command_id(name);
	return command_list[id];
}

bool is_command(char * command)
{
	if (get_command_id(command) > -1) {
		return true;
	}

	return false;
}

int calculate_command_space(char ** commandline)
{
	int numOfOperands = 0;
	int space = 0;

	char * commandName;
	char * dest = NULL;
	char * src = NULL;

	AddressingMode destAddressMode;
	AddressingMode srcAddressMode;

	/* validate that command exists */
	if(!validate_command(commandline)) {
		return 0;
	}

	commandName = commandline[0];

	/* calculate number of operands */
	numOfOperands = calculate_number_of_operands(commandline, commandName);

	/* assign destination and source operands */
	if(numOfOperands == 1) {
		dest = commandline[1];

	} else if(numOfOperands == 2) {
		dest = commandline[2];
		src = commandline[1];
	}

	destAddressMode = addressing_mode_type(dest);
	srcAddressMode = addressing_mode_type(src);

	/* validate that command can use these addressing modes */
	if (!validate_command_addressing_mode(commandName, destAddressMode, srcAddressMode)) {
		return 0;
	}

	space = calculate_space_by_addressing_modes(destAddressMode, srcAddressMode);

	/* free allocated space */
	commandName = NULL;
	dest = NULL;
	src = NULL;
	free(commandName);
	free(dest);
	free(src);

	return space;
}

bool validate_command(char ** commandline)
{
	if(!is_command(commandline[0])) {
		printf("%s is not a valid command on line %d\n", commandline[0], get_file_line());
		set_error_mode();
		return false;
	}

	return true;
}

bool validate_command_addressing_mode(char * name, AddressingMode dest, AddressingMode src)
{
	Command command;
	command = get_command_by_name(name);
	
	/* if a command cannot receive any operands */
	if (is_empty_operands_command(command)) {
		if (is_empty_addressing_mode(dest) && is_empty_addressing_mode(src)) {
			return true;
		} else {
			printf("command %s cannot receive any arguments on line %d\n", command.name, get_file_line());
			set_error_mode();
			return false;
		}
	}

	if (!is_empty_command_operand_src(command)) {
		if (is_empty_addressing_mode(src)) {
			printf("command %s must receive source argument on line %d\n", command.name, get_file_line());
			set_error_mode();
			return false;
		}else if (!is_addressing_mode_allowed_by_command(src, command.allowedAddressingsSrc)) {
			printf("source argument is not allowed by command %s on line %d\n", command.name, get_file_line());
			set_error_mode();
			return false;
		}
	}

	if (!is_empty_command_operand_dest(command)) {
		if (is_empty_addressing_mode(dest)) {
			printf("command %s must receive destination argument on line %d\n", command.name, get_file_line());
			set_error_mode();
			return false;
		}else if (!is_addressing_mode_allowed_by_command(dest, command.allowedAddressingsDest)) {
			printf("destination argument is not allowed by command %s on line %d\n", command.name, get_file_line());
			set_error_mode();
			return false;
		}
	}

	return true;
}

AddressingMode addressing_mode_type(char * operand)
{
	int i = 0;
	bool isArray = false;

	if(operand == NULL) { /* Not Address Mode */
		return NAM;
	} else if (operand[0] == IMMEDIATE_SYMBOL) { /* IMMEDIATE */
		return IMMEDIATE;
	} else if(is_registor_name(operand)) { /* REGISTER */
		/* validate registor name */
		if (!is_valid_registor(operand)) {
			printf("%c is not a valid registor on line %d\n", operand[1], get_file_line());
			set_error_mode();
			return NAM;
		}
		return REGISTER;
	}

	/* INDEXED */
	while(operand[i]) {
		if (operand[i] == '[') {
			isArray = true;
		} else if ((operand[i] == ']') && isArray) {
			return INDEXED;
		}
		i++;
	}

	/* must be DIRECT */
	return DIRECT;
}

bool is_registor_name(char * operand)
{
	if ((strlen(operand) == 2) && (operand[0] == 'r') && (isdigit((int) operand[1]))) {
		return true;
	}

	return false;
}

bool is_valid_registor(char * operand)
{
	/* convert char to int */
	int registorNumber = operand[1] - '0';

	if (registorNumber > MAX_REGISTERS) {
		return false;
	}

	return true;
}

bool is_empty_command_operand_dest(Command command)
{
	if (command.allowedAddressingsDest == NULL) {
		return true;
	}

	return false;
}

bool is_empty_command_operand_src(Command command)
{
	if (command.allowedAddressingsSrc == NULL) {
		return true;
	}

	return false;
}

bool is_empty_operands_command(Command command)
{
	if (is_empty_command_operand_dest(command) && is_empty_command_operand_src(command)) {
		return true;
	}

	return false;
}

bool is_empty_addressing_mode(AddressingMode addressing_mode)
{
	if (addressing_mode == NAM) {
		return true;
	}

	return false;
}

bool is_addressing_mode_allowed_by_command(AddressingMode addressing_mode, AddressingMode * command_allowed)
{
	int i = 0;
	while(command_allowed[i]) {
		if (command_allowed[i] == addressing_mode) {
			return true;
		}
		i++;
	}
	return true;
}

int calculate_space_by_addressing_modes(AddressingMode dest, AddressingMode src)
{
	int space = 1;

	if (is_empty_addressing_mode(dest)) { /* only command */
		return space;
	} else if (dest == REGISTER && src == REGISTER) { /* register type operands share the same memory cell */
		space += 1;
		return space;
	}

	space += calculate_space_by_addressing_mode(dest) + calculate_space_by_addressing_mode(src);
	return space;
}

int calculate_space_by_addressing_mode(AddressingMode addressing_mode)
{
	if (is_empty_addressing_mode(addressing_mode)) {
		return 0;
	} else if (addressing_mode == INDEXED) {
		return 2;
	}

	return 1;
}

int get_instructions_counter(int size)
{
	/* increment counter */
	_IC += size;

	/* return last value */
	return _IC - size;
}

int get_instructions_memory_amount()
{
	return _IC - IC_DEFAULT_VALUE;
}

void reset_instructions_counter()
{
	_IC = IC_DEFAULT_VALUE;
}

int calculate_number_of_operands(char ** commandline, char * commandName)
{
	int i = 0;
	int numOfOperands = 0;

	while(commandline[i]) {
		if(strcmp(commandline[i], commandName) != 0) {
			numOfOperands++;
		}
		i++;
	}

	return numOfOperands;
}

char * get_array_name(char * name)
{
	int i = 0;
	int counter = 0;
	char * newName = (char *) malloc(sizeof(char));
	while(name[i]) {
		if (name[i] == '[') {
			break;
		}
		newName = (char *) realloc(newName, (counter + 1) * sizeof(char));
		newName[counter] = name[i];
		counter++;
		i++;
	}
	newName[counter+1] = '\0';
	return newName;
}

char * get_array_i_value(char * name)
{
	int i = 0;
	int counter = 0;
	bool flag = false;
	char * newName = (char *) malloc(sizeof(char));
	while(name[i]) {
		if (name[i] == '[' || flag) {
			if (name[i] == ']') {
				break;
			}
			if (name[i] != '[') {
				newName = (char *) realloc(newName, (counter + 1) * sizeof(char));
				newName[counter] = name[i];
				counter++;
			}
			flag = true;
		}
		i++;
	}
	newName[counter+1] = '\0';
	return newName;
}

MachineCode get_operand_mchine_code(char * op)
{

	AddressingMode opAdd = addressing_mode_type(op);
	char * name = op;

	if (opAdd == NAM) {
		return A;
	}

	if (opAdd == INDEXED) {
		name = get_array_name(name);
	}

	if (is_symbol_in_list(name)) {
		if (is_symbol_external(name)) {
			return E;
		}

		return R;
	}

	return A;
}

int get_absolute_value(char * str)
{
	int value = 0;
	int i = 1;
	char * noHashtagStr = (char *) malloc(strlen(str) * sizeof(char));

	/* remove '#' */
	while(str[i]) {
		noHashtagStr[i-1] = str[i];
		i++;
	}

	/* get int value */
	if (is_symbol_in_list(noHashtagStr)) {
		value = get_symbol_value_by_name(noHashtagStr);
	} else {
		value = atoi(noHashtagStr);
	}

	/* free allocated space */
	noHashtagStr = NULL;
	free(noHashtagStr);
	return value;
}

int get_register_value(char * reg)
{
	int value = 0;
	value = reg[1] - '0';
	return value;
}

void instruction_to_bits(char ** commandline)
{
	int numOfOperands = 0;
	int commandCode = -1;
	char * dest = NULL;
	char * src = NULL;
	char * commandName;

	AddressingMode destAddressMode;
	AddressingMode srcAddressMode;

	commandName = commandline[0];
	/* calculate number of operands */
	numOfOperands = calculate_number_of_operands(commandline, commandName);

	/* assign destination and source operands */
	if(numOfOperands == 1) {
		dest = commandline[1];

	} else if(numOfOperands == 2) {
		dest = commandline[2];
		src = commandline[1];
	}

	destAddressMode = addressing_mode_type(dest);
	srcAddressMode = addressing_mode_type(src);

	destAddressMode = destAddressMode == NAM ? IMMEDIATE : destAddressMode;
	srcAddressMode = srcAddressMode == NAM ? IMMEDIATE : srcAddressMode;
	commandCode = get_command_id(commandName);

	create_lines(commandCode, srcAddressMode, destAddressMode);
	create_operand_lines(src, dest);
}



void create_lines(int commandCode, int srcAddressMode, int destAddressMode)
{
	OutputLine line;
	char * bits = malloc(CELL_BIT_SIZE * sizeof(char));

	char * commandCodeBits = decimal_to_bin(commandCode, 4);
	char * srcAddressModeBits = decimal_to_bin(srcAddressMode, 2);
	char * destAddressModeBits = decimal_to_bin(destAddressMode, 2);
	/* not in use */
	bits[0] = '0';
	bits[1] = '0';
	bits[2] = '0';
	bits[3] = '0';
	/* command */
	bits[4] = commandCodeBits[0];
	bits[5] = commandCodeBits[1];
	bits[6] = commandCodeBits[2];
	bits[7] = commandCodeBits[3];
	/* src operand */
	bits[8] = srcAddressModeBits[0];
	bits[9] = srcAddressModeBits[1];
	/* dest operand */
	bits[10] = destAddressModeBits[0];
	bits[11] = destAddressModeBits[1];
	/* machine code */
	bits[12] = '0';
	bits[13] = '0';

	line.bits = bits;
	line.lineNumber = get_instructions_counter(1);
	push_line_to_list(line);
}

void create_operand_lines(char * src, char * dest)
{
	AddressingMode srcAddressMode = addressing_mode_type(src);
	AddressingMode destAddressMode = addressing_mode_type(dest);
	bool srcCreated = false;
	bool destCreated = false;

	if (srcAddressMode == REGISTER && destAddressMode == REGISTER) {
		create_single_line_for_registers(src, dest);
		return;
	} else if (srcAddressMode == REGISTER) { /* create register src line */
		create_single_line_for_registers(src, "r0");
		srcCreated = true;
	} else if (destAddressMode == REGISTER) {/* create register dest line */
		create_single_line_for_registers("r0", dest);
		destCreated = true;
	}

	if (!srcCreated) {
		create_operand_line(src, srcAddressMode);
	}

	if (!destCreated) {
		create_operand_line(dest, destAddressMode);
	}
	return;
}

void create_single_line_for_registers(char * src, char * dest)
{
	OutputLine line;
	/*machineCode are;*/ /* AMIR added for A R E bits 16-18 since I don't see it?*/
	int srcVal, destVal;
	char * srcBits;
	char * destBits;
	char * bits = (char *) malloc(CELL_BIT_SIZE*sizeof(char)); /* AMIR changed from 14 to CELL_BIT_SIZE */

	srcVal = get_register_value(src);
	destVal = get_register_value(dest);

	srcBits = decimal_to_bin(srcVal, 3);
	destBits = decimal_to_bin(destVal, 3);

	bits[0] = '0';
	bits[1] = '0';
	bits[2] = '0';
	bits[3] = '0';
	bits[4] = '0';
	bits[5] = '0';
	/* src bits */
	bits[6] = srcBits[0];
	bits[7] = srcBits[1];
	bits[8] = srcBits[2];
	/* dest bits */
	bits[9] = destBits[0];
	bits[10] = destBits[1];
	bits[11] = destBits[2];

	/* machine code */
	bits[12] = '0';
	bits[13] = '0';

	line.bits = bits;
	line.lineNumber = get_instructions_counter(1);
	push_line_to_list(line);

	/* free allocated space */
	srcBits = NULL;
	destBits = NULL;
	bits = NULL;
	free(srcBits);
	free(destBits);
	free(bits);
}

void create_operand_line(char * op, AddressingMode am)
{
	int opValue = 0;
	MachineCode mc;

	if (op == NULL) {
		return;
	}else if (am == INDEXED) {/* handle array type */
		create_array_lines(op);
		return;
	}

	if (op[0] == '#') { /* handle absolute operand value */
		opValue = get_absolute_value(op);
	} else if (am == REGISTER) { /* handle register operand */
		opValue = get_register_value(op);
	} else if (is_symbol_in_list(op)) {
		if (is_symbol_external(op)) { /* handle symbols*/
			add_to_external_list(op, get_instructions_counter(1)); /* add external to list */
			get_instructions_counter(-1);
		}
		opValue = get_symbol_value_by_name(op);
	}

	mc = get_operand_mchine_code(op);
	build_op_line(opValue, mc);
}

void create_array_lines(char * op)
{
	char * arrayLabel = get_array_name(op);
	char * indexName = get_array_i_value(op);
	int labelValue = 0;
	int indexValue = 0;
	MachineCode labelMc;
	MachineCode indexlMc = A;

	if (isdigit(indexName[0]) > 0)
	{ /* is numeric value */
		indexValue = atoi(indexName);
	}
	else if (is_symbol_in_list(indexName))
	{
		indexValue = get_symbol_value_by_name(indexName);
	}
	else
	{
		printf("undefined array index %s on line %d\n", indexName, get_file_line());
		set_error_mode();
	}

	labelValue = get_symbol_value_by_name(arrayLabel);
	labelMc = get_operand_mchine_code(arrayLabel);

	build_op_line(labelValue, labelMc);
	build_op_line(indexValue, indexlMc);
}

void build_op_line(int value, MachineCode mc)
{
	OutputLine line; /* AMIR configured in "output.h" , struct of (lineNumber,*bits) */
	int i = 0;
	int j;
	char * bits = malloc(CELL_BIT_SIZE * sizeof(char));
	char * valueBits = decimal_to_bin(value, 16); /* AMIR changed to from 12 */
	/*char * mcBits = decimal_to_bin(mc, 2); */
	/*        ^  Our ARE isnt signed as 2bits but 3 individuals*/
	
	printf("\n VALUE : %d\n",value);
	/* wanted to see the value .. if value is the number of the opcode then I can easily
	translate it to be the bit that needs to be turned on (just check if equals to then)
	but it seems to be repeating numbers of address in memory I believe for labels & values.
	Need to understand what is the purpose of this value. */
	
	while(i<15) { /* AMIR changed to from 12, to represent 16 opcode bits*/
		bits[i] = valueBits[i];
		i++;
	}
	/* machine code - AMIR this is ARE created in "output.h" so why only 2bits? */
	/* was bits[..] = mcBits[0] and mcBits[1] because he translated the MC to binary and showed all 3 in that binary format; */
	bits[16] = 0; /* A */
	bits[17] = 0; /* R - for entry label's*/
	bits[18] = 0; /* E - for external label's */
	bits[19] = 0; /* Always 0 */
	
	/* AMIR */
	if(mc == 0) /* machine code equals A */
		bits[16] = 1;
	else if(mc == 1) /* machine code equals R */
		bits[17] = 1;
	else 		/* machine code equals E */
		bits[18] = 1;

	/* AMIR DEBUG TO SEE HOW A LINE LOOKS WHEN DONE */
	printf("Line number %d: ", line.lineNumber);
	for(j=0; j<20; j++){
		printf("%d ",bits[j]);
	}
	printf("\n"); /* go down new line */

	line.bits = bits;
	line.lineNumber = get_instructions_counter(1);
	push_line_to_list(line);
}
