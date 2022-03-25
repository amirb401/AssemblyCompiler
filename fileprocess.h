#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h> /* amir */

#define MAX_LINE_INPUT 80
#define COMMENT_SIGN ';'

void process_file(char *filename);
int get_file_line();
char * appendExtension(char *filename);
