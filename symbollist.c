#include "symbollist.h"


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
		printf("type: %d\n",current->symbol.type);
		printf("value: %d\n",current->symbol.value);
		printf("size: %d\n",current->symbol.size);
		printf("isMacro: %d\n",current->symbol.isMacro);
		printf("isExternal: %d\n",current->symbol.isExternal);
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
	} else {
		/* go to last list item*/
		while(current->next != NULL) {
			current = current->next;
		}
		/* push symbol to last item */
		current->next = (symbolListPtr) malloc(sizeof(SymbolListItem));
		current->next->symbol = symbol;
		current->next->next = NULL;
	}
}

/* remove ONE item from list with the name value the same to the given name */
void remove_from_symbol_list(char *nameToRemove)
{
	/* two pointer one is helper that get the priveus node and one that run on the list */
	symbolListPtr current = symbolListHead;
	symbolListPtr helper=symbolListHead-1;
	/*if the list is empty the function return with a messege that the list is empty */
	if(symbolListHead == NULL){
		printf("\n the list is empty\n");
		return;
	}

	/*
	* run on the list with str cmp if value equal to zero
	* (mean that the name is equal to the given) the curret node next replaced with the next
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
	if(current != NULL) {
		while(current != NULL) {
			if (strcmp(current->symbol.name, symbol.name) == 0) {
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
		printf("WARNING: %s declared twice, ignored.\n", symbol.name);
		return;
	}

	push_symbol_to_list(symbol);
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

bool is_symbol_external(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return current->symbol.isExternal;
		}
		current = current->next;
	}

	return false;
}

bool is_symbol_macro(char * name)
{
	symbolListPtr current = symbolListHead;
	while(current != NULL) {
		if (strcmp(current->symbol.name, name) == 0) {
			return current->symbol.isMacro;
		}
		current = current->next;
	}

	return false;
}

bool is_symbol_in_list(char * name)
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
