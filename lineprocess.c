#include "lineprocess.h"
#include "symbollist.h"
#include "symbol.h"

int instructions_memory = 0;

int data_memory = 0;

char ** entry_list = NULL;

extern int get_instructions_counter(int size);

extern int get_data_counter(int size);

extern bool is_command(char * command);

extern int calculate_command_space(char ** commandline);

extern void reset_instructions_counter();

extern void reset_data_counter();

extern void instruction_to_bits(char ** words);

extern void data_to_bits(char ** words);

char ** convert_line_to_words_array(char *line);

bool is_external(char word[]);

bool is_entry(char word[]);

bool is_macro(char word[]);

bool is_symbol_assign(char ** words);

void handle_external_symbol(char ** words);

void handle_macro_symbol(char ** words);

void handle_symbol_assign(char ** words);

void handle_command(char ** words);

void add_to_entry_list(char * entry);

void convert_symbol_assign_to_ouput_item(char ** words);

void convert_command_to_output_item(char ** words);

void convert_data_to_output_item(char ** words);

void reset_memory_counters();

void reset_entry_list();

void first_loop_process(char *line)
{
	char ** words = convert_line_to_words_array(line);

	if(is_entry(words[0])) {/* ignore entry type symbols */
		return;

	}else if(is_external(words[0])) {/* handle external symbols */
		handle_external_symbol(words);
		return;

	}else if(is_macro(words[0])) {/* handle macro symbols */
		handle_macro_symbol(words);
		return;

	}else if(is_symbol_assign(words)) { /* handle symbol assign */
		handle_symbol_assign(words);
		return;

	} else if(is_command(words[0])) { /* handle commands */
		handle_command(words);
		return;
	}


	return;
}

void second_loop_process(char *line)
{
	char ** words = convert_line_to_words_array(line);

	if (is_macro(words[0])) {/* ignore macro */
		return;

	}else if(is_entry(words[0])) { /* add to entry list */
		add_to_entry_list(words[1]);
		return;

	} else if (is_symbol_assign(words)) {/* handle symbols */
		convert_symbol_assign_to_ouput_item(words);
		return;

	} else if (is_command(words[0])) {/* handle commands */
		convert_command_to_output_item(words);
		return;
	}
}

/**
 * converts a string to an array of words without the whitespaces
 */
char ** convert_line_to_words_array(char *line)
{
	char * nextWord;
	char ** wordArray;
	int i = 0;
	char *lineClone;
	wordArray = NULL;
	/* allocate space same as line */
	lineClone = (char *) malloc((strlen(line)+1)* sizeof(char));
	/* clone line */
	strcpy(lineClone, line);
	/*grabs the next word from the string (without whitespaces)*/
	nextWord = strtok(lineClone, WORD_SPLIT_TOKENS);

	while (nextWord != NULL)
	{
		/*reallocating space from the next word in the array*/
		wordArray = (char **) realloc(wordArray, (i + 1) * sizeof(char *));
		/* allocate space for the incoming word*/
		wordArray[i] = (char *) malloc(sizeof(nextWord) * sizeof(char));
		/* actually setting the word */
		wordArray[i] = nextWord;
		/* grabing the next word from the string */
		nextWord = strtok (NULL, WORD_SPLIT_TOKENS);
		i++;
	}

	/* add NULL to last index to indicate the end of the array */
	wordArray = (char **) realloc(wordArray, i * sizeof(char *));
	wordArray[i] = (char *) malloc(sizeof(nextWord) * sizeof(char));
	wordArray[i] = NULL;

	/* free alloctated spaces */
	lineClone = NULL;
	free(lineClone);
	free(nextWord);

	return wordArray;
}

/**
 * checks weather sign is the .external key word
 */
bool is_external(char word[])
{
	if(strcmp(EXTERNAL_SIGN, word) == 0) {
		return true;
	}

	return false;
}

/**
 * checks weather sign is the .entry key word
 */
bool is_entry(char word[])
{
	if(strcmp(ENTRY_SIGN, word) == 0) {
		return true;
	}

	return false;
}

/**
 * checks weather sign is the .define key word
 */
bool is_macro(char word[])
{
	if(strcmp(MACRO_SIGN, word) == 0) {
		return true;
	}

	return false;
}

/**
 * checks weather sign a regular symbol assign
 */
bool is_symbol_assign(char ** words)
{
	int i = 0;
	char * word;
	unsigned wordLength;

	while(words[i]) {
		word = words[i];
		wordLength = strlen(words[i]);
		/* checks if the line is variable assign command */
		if(word[wordLength-1] == SYMBOL_ASSIGN_SIGN) {
			return true;
		}
		i++;
	}
	return false;
}

/**
 * adds symbol to list
 */
void handle_external_symbol(char ** words)
{
	Symbol symbol;

	/* create symbol */
	symbol.name = words[1];
	symbol.type = EMPTY;
	symbol.value = EXTERNAL_ADDRESS_VALUE;
	symbol.size = 0;
	symbol.isMacro = false;
	symbol.isExternal = true;

	/* add to symbols list */
	add_symbol_to_list(symbol);
}

/**
 * adds symbol to list
 */
void handle_macro_symbol(char ** words)
{
	int i = 0;
	Symbol symbol;
	int macroValue;

	/* prepare macro valus */
	while(words[i]) {
		/* get value after "=" sign */
		if(strcmp(words[i], "=") == 0) {
			macroValue = atoi(words[i+1]);
			break;
		}
		i++;
	}

	/* prepare symbol */
	symbol.name = words[1];
	symbol.type = EMPTY;
	symbol.value = macroValue;
	symbol.size = 1;
	symbol.isMacro = true;
	symbol.isExternal = false;

	/* add to symbols list */
	add_symbol_to_list(symbol);
}

void handle_symbol_assign(char ** words)
{
	Symbol symbol;
	char * symbolName;
	SymbolType symbolType;
	int size;
	int value;

	symbolName = get_symbol_name(words);
	symbolType = get_symbol_type(words);
	size = calculate_symbol_memory_size(words, symbolType, symbolName);

	/* differrent value for data and instructions */
	if (symbolType == COMMAND) {
		value = get_instructions_counter(size);
	} else if (symbolType == DATA) {
		value = get_data_counter(size);
	}

	/* create symbol */
	symbol.name = symbolName;
	symbol.type = symbolType;
	symbol.value = value;
	symbol.size = size;
	symbol.isMacro = false;
	symbol.isExternal = false;

	add_symbol_to_list(symbol);

	/* free allocated space */
	symbolName = NULL;
	free(symbolName);
}

void handle_command(char ** words)
{
	int size = calculate_command_space(words);
	/* only increment counter */
	get_instructions_counter(size);
}

void update_data_symbols_addresses()
{
	int ic = get_instructions_counter(0);

	symbolListPtr current = symbolListHead;

	while(current != NULL) {
		/* only data symbols */
		if (current->symbol.type == DATA) {
			/* updates adres after end of ic*/
			current->symbol.value += ic;
		}
		current = current->next;
	}
}

void reset_counters()
{
	reset_instructions_counter();
	reset_data_counter();
}

void set_saved_memory_cells(int instructions, int data)
{
	instructions_memory = instructions;
	data_memory = data;
}

void add_to_entry_list(char * entry)
{
	int i = 0;
	if (entry_list != NULL) {
		while(entry_list[i]) {
			i++;
		}
	}
	entry_list = (char **) realloc(entry_list, (i + 1) * sizeof(char *));
	entry_list[i] = (char *) malloc(sizeof(entry));
	entry_list[i] = entry;

	return;
}

void convert_symbol_assign_to_ouput_item(char ** words)
{
	char * name;
	char ** action;
	name = get_symbol_name(words);
	action = remove_symbol_name(words, name);

	if (is_command(action[0])) {
		convert_command_to_output_item(action);
	} else { /* is data symbol */
		convert_data_to_output_item(action);
	}
}

void convert_command_to_output_item(char ** words)
{
	instruction_to_bits(words);
}

void convert_data_to_output_item(char ** words)
{
	data_to_bits(words);
}

void reset_memory_counters()
{
	instructions_memory = 0;
	data_memory = 0;
	reset_entry_list();
}

void reset_entry_list()
{
	int i = 0;
	if (entry_list) {
		while(entry_list[i]) {
			entry_list[i] = NULL;
			free(entry_list[i]);
			i++;
		}
	}
}
