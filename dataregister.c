#include "dataregister.h"
#include "output.h"

int _DC = DEFAULT_VALUE;

extern int get_file_line();

extern void set_error_mode();

extern int get_instructions_counter(int size);


extern int get_symbol_value_by_name(char * name);

DataType get_data_type(char ** data);

bool validate_data(char ** data, DataType type);

bool validate_data_type(char **data);

bool validate_string_type(char **data);

int calculate_data_type(char ** data);

int calculate_string_type(char ** data);

void reset_data_counter();

void string_to_bin(char ** words);

void char_to_bin(char c);

void data_array_to_bin(char ** words);

bool string_is_number(char * s);

int calculate_data_space(char ** data)
{
	int size = 0;
	DataType type = get_data_type(data);

	if (!validate_data(data, type)) {
		return 0;
	}

	if (type == DAT_TYPE) {
		size = calculate_data_type(data);
	}
	else if (type == STRIN_TYPE) {
		size = calculate_string_type(data);
	}
	else if (type == ENT_TYPE) {
		size = calculate_string_type(data); /* anat add calc_entry_type */
	}
	else if (type == EXT_TYPE) {
		size = calculate_string_type(data); /* anat add calc_external_type */
	}
	return size;
}

bool validate_data(char ** data, DataType type)
{
	/* if type data */
	if (type == DAT_TYPE) {
		return validate_data_type(data);

	} else if (type == STRIN_TYPE) { /* if is string */
		return validate_string_type(data);

	}

	printf("undefined data type %s in line %d\n", data[0], get_file_line());
	set_error_mode();
	return false;
}

bool validate_data_type(char **data)
{
	/* TODO validate data*/
	return true;
}

bool validate_string_type(char **data)
{
	/* TODO validate string*/
	return true;
}

DataType get_data_type(char ** data) /* anat ---------------- */
{
	if (strcmp(data[0], DATA_TYPE_SYMBOL) == 0) {
		return DAT_TYPE;
	}
	else if (strcmp(data[0], STRING_TYPE_SYMBOL) == 0) {
		return STRIN_TYPE; /* maybe return DAT_TYPE; */
	}
	else if (strcmp(data[0], ENT_TYPE_SYMBOL) == 0) {
		return ENT_TYPE;
	}
	else if (strcmp(data[0], EXT_TYPE_SYMBOL) == 0) {
		return EXT_TYPE;
	}

	return ND_T;
}

int calculate_data_type(char ** data)
{
	int i = 1;

	while(data[i]) {
		i++;
	}

	return i-1;
}

int calculate_string_type(char ** data)
{
	int i = 0;
	int counter = 0;

	while(data[1][i]) {
		if (isalpha(data[1][i])) {
			counter++;
		}
		i++;
	}
	/* for NULL */
	counter++;
	return counter;
}

int get_data_counter(int size)
{
	/* increment counter */
	_DC += size;
	/* return last value */
	return _DC-size;
}

int get_data_memory_amount()
{
	return _DC - DEFAULT_VALUE;
}

void reset_data_counter()
{
	_DC = DEFAULT_VALUE;
}

void data_to_bits(char ** words)
{
	if (strcmp(words[0], STRING_TYPE_SYMBOL) == 0) {
		string_to_bin(words);
	} else if (strcmp(words[0], DATA_TYPE_SYMBOL) == 0) {
		data_array_to_bin(words);
	}
}

void string_to_bin(char ** words)
{
	OutputLine line;
	int i = 0;
	char * string = words[1];

	while(string[i]) {
		if (isalpha(string[i])) {
			char_to_bin(string[i]);
		}
		i++;
	}
	/* add end of string */
	line.lineNumber = get_instructions_counter(1);
	line.bits = decimal_to_bin(0, 20);
	push_line_to_list(line);

	/* free allocated space */
	string = NULL;
	free(string);
}

void char_to_bin(char c)
{
	OutputLine line;
	int value = c - '0';

	line.lineNumber = get_instructions_counter(1);
	line.bits = decimal_to_bin(value, 20);
	push_line_to_list(line);
}

void data_array_to_bin(char ** words)
{
	OutputLine line;
	int i = 1;
	int value = 0;

	while(words[i]) {
		
		if (!string_is_number(words[i])) {
			value = 999; /* anat */
		} else {
			value = atoi(words[i]);
		}

		line.lineNumber = get_instructions_counter(1);
		line.bits = decimal_to_bin(value, 20);
		push_line_to_list(line);
		i++;
	}

}



bool string_is_number(char * s)
{
	int i = 0;
	while(s[i]) {
		if (!isdigit(s[i]) && s[i] != '-' && s[i] != '+') {
			return false;
		}
		i++;
	}

	return true;
}
