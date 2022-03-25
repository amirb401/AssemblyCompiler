#include "symbollist.h"
#include "symbol.h"


/**
 * print all the values in the list for the head node to EOF
 * if the list is empty print to the user
 */
void print_symbol_list()
{
	symbolListPtr current = symbolListHead;

	if(symbolListHead == NULL) {
		printf("\n the list is empty\n");
		return;
	}
	printf("--------Symbols List-------\n");
	while(current != NULL) {
		printf("--------------------------\n");
		printf("name: %s\n",current->symbol.name);
		printf("type: %d\n",current->symbol.attrType);
		printf("value: %d\n",current->symbol.value);
		printf("base: %d\n",current->symbol.baseAddr);
		printf("offset: %d\n",current->symbol.offset);
		printf("--------------------------\n");
		current = current->next;
	}
}

void push_symbol_to_list(Symbol symbol)
{
	symbolListPtr current = symbolListHead;
	/* if head is empty*/
	if(symbolListHead == NULL) {
		/* push item to head*/
		symbolListHead = (symbolListPtr) malloc(sizeof(SymbolListItem));
		symbolListHead->symbol = symbol;
		symbolListHead->next = NULL;
	}
	else {
		/* go to last list item*/
		while(current->next != NULL) {
			current = current->next;
		}
		/*if (is_in_symbol_list(symbol)) {
			/* add attribute anat --------- */
			/* if it exists but we need to add an attribute to the table */

		/*}*/
		/*else { /* doesn't exists */
			/* push symbol to last item */
			current->next = (symbolListPtr) malloc(sizeof(SymbolListItem));
			current->next->symbol = symbol;
			current->next->next = NULL;

	}
}

/* remove ONE item from list with the name value the same to the given name */
void remove_from_symbol_list(char *nameToRemove)
{
	/* two pointer one is helper that get the previous node and one that run on the list */
	symbolListPtr current = symbolListHead;
	symbolListPtr helper = symbolListHead-1;
	/*if the list is empty the function return with a message that the list is empty */
	if(symbolListHead == NULL){
		printf("\n the list is empty\n");
		return;
	}

	/*
	* run on the list with str cmp if value equal to zero
	* (mean that the name is equal to the given) the current node next replaced with the next
	* of the helper and get freed then the function break.
	 */
	while(current->next != NULL) {
		if (strcmp(current->symbol.name, nameToRemove) == 0)
		{
			helper->next=current->next;
			free(current);
			break;
		}
		current = current->next;
		helper = helper->next;

	}
}

bool is_in_symbol_list(Symbol symbol)
{
	symbolListPtr current = symbolListHead;

	if(current != NULL) { /* should we remove this if? anat */
		while(current != NULL) {
			if ((strcmp(current->symbol.name, symbol.name) == 0) ) /* anat amir */
			{
				return true;
			}
			current = current->next;
		}
	}

	return false;
}

void add_symbol_to_list(Symbol symbol)
{
	if(is_in_symbol_list(symbol)) {
		/* anat we need to change it. we can have the same name if its: .entry LABEL (example) */
		printf("WARNING: %s declared twice, ignored.\n", symbol.name);
		return;
	}

	push_symbol_to_list(symbol); /* we need to push only labels, shouldn't we? */
}

int get_symbol_value_by_name(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return current->symbol.value;
		}
		current = current->next;
	}

	return -1;
}
/* anat it was bool and i've change it to int */
int is_symbol_external(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return current->symbol.attrType = EXTERNAL; /* anat */
		}
		current = current->next;
	}

	return -1; /* false anat */
}

/* anat it was bool and i've change it to int */
int is_symbol_code(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return current->symbol.attrType = CODE; /* anat */
		}
		current = current->next;
	}

	return -1; /* false anat */
}

/* anat it was bool and i've change it to int */
int is_symbol_entry(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) { /* equals */
			return current->symbol.attrType = ENTRY; /* anat */
		}
		current = current->next;
	}

	return -1; /* false anat */
}

/* anat it was bool and i've change it to int */
int is_symbol_data(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) { /* equals */
			return current->symbol.attrType = DATA; /* anat */
		}
		current = current->next;
	}

	return -1; /* false anat */
}


bool is_symbol_in_list(char * name) /* duplicated anat search: is_in_symbol_list */
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return true;
		}
		current = current->next;
	}

	return false;
}

void reset_symbol_list()
{
	symbolListPtr current = symbolListHead;
	while(current) {
		current->symbol.name = NULL;
		free(current->symbol.name);
		free(current);
		current = current->next;
	}
	symbolListHead = NULL;
}
