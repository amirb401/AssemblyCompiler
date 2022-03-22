#include "output.h"

extern int instructions_memory;

extern int data_memory;

extern char ** entry_list;

OutputLinePtr outputLineHead = NULL;

ExternalItemList * external_list = NULL;

char outputLineSymbols [5] = {
	'A',
	'B',
	'C',
	'D',
	'E'
};

extern int get_symbol_value_by_name(char * name);

void push_line_to_list(OutputLine line)
{
	OutputLinePtr current = outputLineHead;
	/* if head is empty*/
	if(outputLineHead == NULL) {
		/* push item to head*/
		outputLineHead = (OutputLinePtr) malloc(sizeof(OutputLineItem));
		outputLineHead->line = line;
		outputLineHead->next = NULL;
	} else {
		/* go to last list item*/
		while(current->next != NULL) {
			current = (OutputLinePtr) current->next;
		}
		/* push line to last item */
		current->next = (OutputLinePtr) malloc(sizeof(OutputLineItem));
		current->next->line = line;
		current->next->next = NULL;
	}
}

void print_outputline_list()
{
	OutputLinePtr current = outputLineHead;

	if(outputLineHead == NULL) {
		printf("\n the list is empty\n");
		return;
	}
	printf("--------Outputline List-------\n");
	while(current != NULL) {
		printf("--------------------------\n");
		printf("line number: %d\n",current->line.lineNumber);
		printf("data: %s\n", current->line.bits);
		printf("--------------------------\n");
		current = current->next;
	}
}

 /*function that take a nuber and make it a bit with the given size */
char * decimal_to_bin(int n,int s)
{
	int c, d, count;
	char *pointer;

	count = 0;
	pointer = (char*)malloc(s+1);

	for (c = s-1; c >= 0; c--) {
		d = n >> c;
		if (d & 1) {
			*(pointer+count) = 1 + '0';
		} else {
			*(pointer+count) = 0 + '0';
		}
		count++;
	}
	*(pointer+count) = '\0';
	return pointer;
}


int bin_to_decimal(char * bits)
{
	int i = 0;
	int dec = 0;

	while (bits[i]) {
		if (bits[i] == '1'){
			dec = dec * 2 + 1;
		} else if (bits[i] == '0') {
			dec *= 2;
		}
		i++;
	}
	return dec;
}

void reset_output_list()
{
	OutputLinePtr current = outputLineHead;
	while(current) {
		current->line.bits = NULL;
		free(current->line.bits);
		free(current);
		current = current->next;
	}
	outputLineHead = NULL;
}

void add_to_external_list(char * name, int line)
{
	ExternalItem external_item;
	ExternalItemList * current = external_list;
	external_item.line = line;
	external_item.symbol = name;

	if(external_list == NULL) {
		external_list = (ExternalItemList *) malloc(sizeof(ExternalItemList));
		external_list->external = external_item;
		external_list->next = NULL;
	} else {
		while(current->next) {
			current = current->next;
		}
		current->next = (ExternalItemList *) malloc(sizeof(ExternalItemList));
		current->next->external = external_item;
		current->next->next = NULL;
	}

	return;
}

void reset_external_list()
{
	ExternalItemList * current = external_list;
	while(current) {
		current->external.symbol = NULL;
		free(current->external.symbol);
		free(current);
		current = current->next;
	}
	external_list = NULL;
}

char * concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void create_output_files(char * filename)
{
	char * ofilename = concat(filename, ".ob");
	char * extfilename = concat(filename, ".ext");
	char * entfilename = concat(filename, ".ent");

	create_o_file(ofilename);
	create_ext_file(extfilename);
	create_ent_file(entfilename);
}

void create_o_file(char * filename)
{
	FILE *file;
	OutputLinePtr current = outputLineHead;
	file = fopen(filename, "w");

	fprintf(file, "  %d %d\n", instructions_memory, data_memory);
	while(current) {
		fprintf(file, "%d  %s\n", current->line.lineNumber, bits_to_special_base4(current->line.bits));
		current = current->next;
	}
	fclose(file);
}

char * bits_to_special_base4(char * bits)
{
	int i = 0;
	int index = 0;
	char * currentBits = (char *) malloc(3 * sizeof(char));
	char * symbolLine = (char *) malloc((strlen(bits)/2) * sizeof(char));

	/* TODO add special 4 base logic */
	while(bits[i]) {
		currentBits[0] = bits[i];
		currentBits[1] = bits[i+1];
		currentBits[2] = '\0';
		index = bin_to_decimal(currentBits);
		symbolLine[(i+1)/2] = outputLineSymbols[index];
		i+=2;
	}
	return symbolLine;
}

void create_ext_file(char * filename)
{
	FILE *file;
	ExternalItemList * current = external_list;

	if (!current) { /* do not create unnecessery file */
		return;
	}

	file = fopen(filename, "w");
	while(current) {
		fprintf(file, "%s %d\n", current->external.symbol, current->external.line);
		current = current->next;
	}
	fclose(file);
}

void create_ent_file(char * filename)
{
	FILE *file;
	int i = 0;

	if (!entry_list) { /* do not create unnecessery file */
		return;
	}

	file = fopen(filename, "w");
	while(entry_list[i]) {
		fprintf(file, "%s %d\n", entry_list[i], get_symbol_value_by_name(entry_list[i]));
		i++;
	}
	fclose(file);
}
