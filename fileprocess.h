#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_INPUT 80
#define COMMENT_SIGN ';'

void process_file(char *filename);
int get_file_line();
