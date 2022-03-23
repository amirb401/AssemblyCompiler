#include "symbol.h"
#include "symbollist.h"
#include "instructionsregister.h"
#include "dataregister.h"

extern int get_file_line();

extern void set_error_mode();

bool is_valid_symbol_data_type(char * type);

bool is_valid_symbol_command_type(char * command);

/**
 * returns symbol name/label
 */
char * get_symbol_name(char ** words)
{
	int i = 0;
	char * word;
	char * name;
	unsigned wordLength;

	while(words[i]) {
		word = words[i];
		wordLength = strlen(words[i]);
		if(word[wordLength-1] == SYMBOL_ASSIGN_SIGN) {
			name = (char *) malloc(wordLength * sizeof(char));
			strncat(name, word, wordLength-1);
			break;
		}
		i++;
	}

	return name;
}

unsigned int get_symbol_type(char ** words) /* anat i think that according to this we should insert to the symbols table*/
{ /* anat so we should add more ifs and whiles */
	int i = 0;
	SymbolType type;

	while(words[i]) {
		/* word starts with DATA initializer */
		if (words[i][0] == '.')
		{
			/* validate approved type */
			if(!is_valid_symbol_data_type(words[i]))
			{
				printf("unknown data type %s on line %d\n", words[i], get_file_line());
				set_error_mode();
			}

			if ((strcmp(words[i], DATA_TYPE_DATA) == 0) || (strcmp(words[i], DATA_TYPE_STRING) == 0))
			{
				type = DATA;
				break;
			}
			else if ((strcmp(words[i], DATA_TYPE_ENTRY) == 0))
			{
				type = ENTRY;
				break;
			}
			else if((strcmp(words[i], DATA_TYPE_EXTERN) == 0))
			{
				type = EXTERNAL;
				break;
			}

		}
		i++;
	}

	if(type != DATA && type != ENTRY && type != EXTERNAL) {
		/* validate COMMAND type */
		if(!is_valid_symbol_command_type(words[1]))
		{
			printf("unknown command %s on line %d\n", words[1], get_file_line());
			set_error_mode();
		}

		type = CODE; /* anat COMMAND was here */
	}

	return type;
}

unsigned int calculate_symbol_memory_size(char ** words, int type, char * name)
{
	unsigned int size = 0;
	char ** data;

	/* only data without symbol name */
	data = remove_symbol_name(words, name);

	if (type == ENTRY) { /* anat COMMAND was here */
		/* calculate command */
		size = calculate_command_space(data);
	} else if (type == DATA) {
		/* calculate data */
		size = calculate_data_space(data);
	}

	return size;
}

char ** remove_symbol_name(char ** words, char * name)
{
	int i = 0;
	int counter = 0;
	char ** newWords = NULL;
	/* clone name */
	char * nameClone = (char *) malloc(strlen(name) * sizeof(char));
	strcpy(nameClone, name);
	/* concat assign symbol to match the one in the original file */
	strcat(nameClone, ":");

	/**
	* copy words array without symbols name
	*/
	while(words[i]) {
		if(strcmp(nameClone, words[i]) != 0) {
			/*reallocating space from the next word in the array*/
			newWords = (char **) realloc(newWords, (counter + 1) * sizeof(char *));
			/* allocate space for the incoming word*/
			newWords[counter] = (char *) malloc(sizeof(words[i]) * sizeof(char));
			/* actually setting the word */
			newWords[counter] = words[i];
			counter++;
		}
		i++;
	}

	/* add NULL to last index to indicate the end of the array */
	newWords = (char **) realloc(newWords, counter * sizeof(char *));
	newWords[counter] = (char *) malloc(sizeof(char));
	newWords[counter] = NULL;

	/*free space*/
	nameClone = NULL;
	free(nameClone);

	return newWords;
}

bool is_valid_symbol_data_type(char * type)
{
	if((strcmp(type, DATA_TYPE_DATA) == 0) || (strcmp(type, DATA_TYPE_STRING) == 0)
			|| (strcmp(type, DATA_TYPE_ENTRY) == 0) || (strcmp(type, DATA_TYPE_EXTERN) == 0)) {
		return true;
	}

	return false;
}

bool is_valid_symbol_command_type(char * command)
{
	if(is_command(command)) {
		return true;
	}
	return false;
}
