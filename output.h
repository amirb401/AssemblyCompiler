#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CELL_BIT_SIZE 20

typedef enum machineCode {
	A,
	E,
	R
} MachineCode;


typedef struct outputLine {
	int lineNumber;
	char *bits;
} OutputLine;


typedef struct outputLineItem * OutputLinePtr;

/* output line for *.o files */
typedef struct outputLineItem {
	OutputLine line;
	OutputLinePtr next;
} OutputLineItem;

/* external symbol for linker to complete */
typedef struct {
	int line;
	char * symbol;
} ExternalItem;

typedef struct external_item_list {
	ExternalItem external;
	struct external_item_list * next;
} ExternalItemList;

void push_line_to_list(OutputLine line);

void print_outputline_list();

char * decimal_to_bin(int n,int s);

int bin_to_decimal(char * bits);

void reset_output_list();

void add_to_external_list(char * name, int line);

void reset_external_list();

void create_output_files(char * filename);

char * concat(const char *s1, const char *s2);

void create_o_file(char * filename);

void create_ext_file(char * filename);

void create_ent_file(char * filename);

char * bits_to_special_base4(char * bits);
