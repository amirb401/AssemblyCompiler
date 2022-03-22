#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "utils.h"
#include "code.h"

/* --- is_int in his code anat remove delete */
/* checks that the value is whole number */
int isWholeNum (char *valToCheck) 
{
	int i;

	/* if the value to check begins with minus or plus increase the current place */
	if (valToCheck[0] == '-' || valToCheck[0] == '+')
	{
		valToCheck++;
	}
	
	/* check if value is a number */
	for (i = 0 ; valToCheck[i]; i++)
	{
		if (!isdigit(valToCheck[i]))
		{
			return 0; /* false, not a number */
		}
	}

	return i > 0; /* if i == 0, the valToCheck is empty anat */
} /* end isWholeNum */


/* --- is_valid_label_name in his code anat remove delete */
/* checks if the value is a valid label */
int isValidLbl (char *lblToCheck)
{
	/* max length of a label is 31 chars ; isalph for the first char ; isalnum for the following letters or digits  */
	/* i think we need to insert a for to loop over the lblToCheck anat */
	if ( ((lblToCheck[0] && strlen(lblToCheck)) <= 31) && (isalph(lblToCheck[0]) && isalnum(lblToCheck + 1) && !isReserved(lblToCheck) )   )
	{
		return 1; /* label name is valid */
	}
	else
	{
		return 0; /* label name is not valid */
	}
} /* end isValidLbl */

/* --- is_reserved_word in his code anat remove delete */
/* check if the value is reserved from opcode and funct */
int isReserved (char *valToGet)
{
	int opc, func;

	getOppOCFun(valToGet, &opc, (funct *) &fun); /* anat to check */

	if (opc != NA_OC || getRegiVal(valToGet) != NA_REG || getSenteTypeName(valToGet) != NA_TYPE)
	{
		return 1; /* the valToGet is reserved */
	}
	
	return 0; /* the valToGet is not reserved */
} /* end isReserved */

/* --- instruction_lookup_item in his code anat remove delete */
/* search sentence type */
struct senteTypeSearch
{
	char *searchTypeVal;
	senteType sType;
}; /* end struct senteTypeSearch */


/* --- instruction_lookup_item instructions_lookup_table[] in his code anat remove delete */
/* search sentence types table */
static struct senteTypeSearch searchTypeTbl[] = {
	{"data", DATA_TYPE},
	{"string", STR_TYPE},
	{"entry", ENTRY_TYPE},
	{"extern", EXTERN_TYPE},
	{NULL, NA_TYPE}
}; /* end structs senteTypeSearch */


/* --- instruction find_instruction_by_name in his code anat remove delete */
/* get sentence type */
senteType getSenteTypeName (char *valToCheck)
{
	struct senteTypeSearch *sts;
	
	for (sts = searchTypeTbl; sts->valToCheck != NULL; sts++)
	{
		if (strcmp(sts->valToCheck, valToCheck) == 0)
		{
			return sts->sType;
		}
	}
	/* not sentence type found */
	return NA_TYPE;
} /* end senteType getSenteTypeName */


/* --- malloc_with_check in his code anat remove delete */
/* i think we have another function to check the malloc fail anat  */
void *tryToMalloc(long size)
{
	void *p = malloc(size);

	if (p == NULL)
	{
		printf("ERROR! COULDN'T MALLOC. EXITING...");
		exit(1); /* program exit with errors */
	}
	return p; /* pointer to the memory if success anat */	
} /* end tryToMalloc */





