/**
* structure of a link list that contain a struct of a symbol with parameters
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* type of symbol */
typedef enum symbolType {
	EXTERNAL,
	CODE,
	ENTRY,
	DATA
} SymbolType;


/* the struct and the parameters of a symbol */
typedef struct {
	char *name; /* symbol name */
	enum symbolType attrType; /* attribute types */
	int value; /* value of address in memory in decimal */
	int baseAddr; /* base address */
	int offset; /* offset */

} Symbol;

/* struct of pointer for the node next parameter ד*/
typedef struct node * symbolListPtr;

/* node deceleration */
typedef struct node {
	Symbol symbol;
	symbolListPtr next;
} SymbolListItem;

/* list head */
symbolListPtr symbolListHead;

/* print symbol list */
void print_symbol_list();

/* push symbol to list */
void push_symbol_to_list(Symbol);

/* remove node from symbol to list */
void remove_from_symbol_list(char *nameToRemove);

bool is_in_symbol_list(Symbol symbol);

void add_symbol_to_list(Symbol symbol);

int get_symbol_value_by_name(char * name);

bool is_symbol_external(char * name);

bool is_symbol_macro(char * name);

bool is_symbol_in_list(char * name);

void reset_symbol_list();
