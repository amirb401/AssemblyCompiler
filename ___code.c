#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "code.h"
#include "utils.h"

#define MAX_OPERAND 2 /* max operand allowed */

/* --- cmd_lookup_element in his code anat remove delete */
/* opcode-funct search table */
struct opcFuncSearchTbl
{
	char *oppr; /* operation */
	opcode opc; /* opcode */
	funct func; /* funct */
	
}; /* end struct opcFuncSearchTbl */


/* --- cmd_lookup_element lookup_table[] in his code anat remove delete */
/* search table for opcode and funct according to operation's name */
static struct opcFuncSearchTbl searchTbl[] = {
	{"mov", MOV_OC, NA_FUNCT},
	{"cmp", CMP_OC, NA_FUNCT},
	{"add", ADD_OC, ADD_FUNCT},
	{"sub", SUB_OC, SUB_FUNCT},
	{"lea", LEA_OC, NA_FUNCT},
	{"clr", CLR_OC, CLR_FUNCT},
	{"not", NOT_OC, NOT_FUNCT},
	{"inc", INC_OC, INC_FUNCT},
	{"dec", DEC_OC, DEC_FUNCT},
	{"jmp", JMP_OC, JMP_FUNCT},
	{"bne", BNE_OC, BNE_FUNCT},
	{"jsr", JSR_OC, JSR_FUNCT},
	{"red", RED_OC, NA_FUNCT},
	{"prn", PRN_OC, NA_FUNCT},
	{"rts", RTS_OC, NA_FUNCT},
	{"stop", STOP_OC, NA_FUNCT},
	{NULL, NA_OC, NA_FUNCT} /* anat maybe remove */

}; /* end struct opcFuncSearchTbl */

/* --- get_opcode_func in his code anat remove delete */
/* gets the operation opcode and funct according to the operation's value */
void getOppOCFun (char *oppr, opcode *destOpc, funct *destFunc)
{
	struct opcFuncSearchTbl *ost;
	*destOpc = NA_OC;
	*destFunc = NA_FUNCT;
	
	/* going over the opcode-funct search table */
	for (ost = searchTbl; ost->oppr != NULL; ost++) {
		/* compare operations, and if they are the same, return the opcode anat */
		if (strcmp(ost->oppr, oppr) == 0)
		{
			*destOpc = ost->opc;
			*destFunc = ost->func;
			return; /* anat do you have return in void?? */
		}		
	}
} /* end getOppOCFun */

/* --- addressing_type get_addressing_type in his code anat remove delete */
/* gets the operand addressing mode according to the operand's value */
addressingModes getAddressMode(char *operandVal)
{
	int i = 0;
	int inxFlag = 0; /* flag for index. set to no */

	/* if null value, return NA */
	if (operandVal[0] == '\0')
	{
		return NA_ADDR;
	}

	/* if the value starts with '#' followed by a number, return immediate addressing */
	if (operandVal[0] == '#' && isWholeNum(operandVal + 1))
	{
		return IMME_ADDR;
	}

	/* if valid label, return direct addressing anat maybe need to add the offset and base? */
	else if (isValidLbl(operandVal))
	{
		return DIR_ADDR;
	}


	/* need to make sure it works lol anat this is the mov x[r10] we saw */
	/*else if (isValidLbl(operandVal) && (operandVal + 1) == '[' && (operandVal + 2) == 'r' && (operandVal + 3) >= 0 && (operandVal + 3) >= 15)
	{
		return INDX_ADDR; /* edit anat */
	/*}*/

	/* if first char is 'r' and the next char is a number between 0-15 followed by space, return Register direct addressing */
	else if (operandVal[0] == 'r' && operandVal[1] >= 0 && operandVal[1] <= 15 && operandVal[2] == '\0')
	{
		return REGI_DIR_ADDR;
	}
	/* if we use this we need to remove the first if, i think anat 
	else
	{
		return NA_ADDR;
	}*/

	while (operandVal[i])
	{
		if (operandVal[i] == '[')
		{
			inxFlag = 1; /* index flag. set to yes */
		}
		else if ((operandVal[i] == ']') && inxFlag == 0) /* maybe 1 anat */
		{
			return INDX_ADDR;
		}
		i++;
	} /* end while */

} /* end addressing modes getAddressMode */


/* --- reg get_register_by_name in his code anat remove delete */
/* gets the register value and checks if its valid */
registers getRegiVal (char *valToGet)
{
	if (strlen(valToGet) == 2) /* r0 - r9 */
	{
		if (valToGet[0] == 'r' && isdigit((int) valToGet[1]) && valToGet[2] == '\0')
		{
			/* converts char to digit */
			int regiNum = valToGet[1] - '0';

			/* we have 0-9 single digit registers */
			if (regiNum >= 0 && regiNum <= 9)
			{
				return regiNum; /* returns the register number */
			}
		}	

	}
	else if (strlen(valToGet) == 3) /* r10 - r15 */
	{
		if (valToGet[0] == 'r' && isdigit((int) valToGet[1]) && isdigit((int) valToGet[2]) && valToGet[3] == '\0')
		{
			/* converts char to digit */
			int regiFirstNum = valToGet[1] - '0';
			int regiSecondNum = valToGet[2] - '0';
			int *regiNum;
			regiNum[0] = regiFirstNum;
			regiNum[1] = regiSecondNum;

			/* we have 10-15 two digits registers */
			if (regiNum >= 10 && regiNum <= 15)
			{
				return regiNum; /* returns the register number */
			}
		}
	} /* end else if */

	/* no register found */
	return NA_REG;
} /* end registers getRegiVal */


/* --- validate_operand_by_opcode in his code anat remove delete */
/* opcode check operand allwoed according to groups */
int opcodeGroupsCheck (opcode opc, int countOC)
{
	if (opc >= RTS_OC && opc <= STOP_OC ) /* third group. should have zero operands */
	{
		if (countOC > 0)
		{
			/* anat amir add printErrToFile func */
			printErrToFile("%d Operands Ditected! No Operands should exist!", countOC);
			return 0; /* error. expected 0 operands */
		}
	} 
	else if (opc >= CLR_OC && opc <= PRN_OC) /* second group. clr,not,inc,dec,jmp,bne,jsr,red,prn. gets 1 operand */
	{
		if (countOC < 1)
		{
			/* anat amir add printErrToFile func */
			printErrToFile("No Operands Ditected! One Operand should exist!");
			return 0; /* error. expected 1 operand */
		}
		else if (countOC > 1)
		{
			/* anat amir add printErrToFile func */
			printErrToFile("%d Operands Ditected! Only 1 Operand should exist!", countOC);
			return 0; /* error. expected 1 operand */
		}
	}
	else if (opc >= MOV_OC && opc <= LEA_OC) /* first group. mov, cmp, add, sub. gets 2 operands */
	{
		if (countOC == 0)
		{
			/* anat amir add printErrToFile func */
			printErrToFile("No Operands Ditected! 2 Operands should exist!");
			return 0; /* error. expected 2 operands */
		}
		else if (countOC > 2 || countOC == 1)
		{
			/* anat amir add printErrToFile func */
			printErrToFile("%d Operands Ditected! 2 Operands should exist!", countOC);
			return 0; /* error. expected 2 operands */
		}	
	}
	return 1; /* all good */ 
	
} /* end opcodeGroupsCheck */


/* --- code_word *get_code_word in his code anat remove delete */
/*  */
multiWord *createMultiWord (opcode opc, funct fnc, int countOC, char *operandVal[MAX_OPERAND])
{
	multiWord *mw;
	/* check addressing modes */
	addressingModes firstMode = countOC >= 1 ? getAddressMode(operandVal[0]) : NA_ADDR;
	addressingModes secondMode = countOC == 2 ? getAddressMode(operandVal[1]) : NA_ADDR;

	if (opcodeGroupsCheck(opc, countOC) == 0) 
	{
		return 0; /* error. operands issues */
	}

	mw = (multiWord *)tryToMalloc(sizeof(multiWord));
	
	/* set all to 0 */
	mw->destAddr = mw->destRegi = mw->srcAddr = mw->srcRegi = 0;
	mw->opcode = opc; /* i think we need to change it anat */
	mw->funct = fnc; /* i think we need to change it anat */
	mw->ARE = ((1 << 2) & 0xFF); /* maybe instead of 2 set it to 16? anat have no idea why he added 0xFF (= 255)  */
	mw->CONST = 0;

	/* check if need to turn on (set to 1) a bit anat */
	if (opc >= MOV_OC && opc <= LEA_OC) /* first group. gets 2 operands */
	{
		mw->srcAddr = firstMode;
		mw->destAddr = secondMode;
		
		/* have no idea what he did here anat */
		if (firstMode == REGI_DIR_ADDR)
		{
			mw->srcRegi = getRegiVal(operandVal[0]);
		}

		if (secondMode == REGI_DIR_ADDR)
		{
			mw->destRegi = getRegiVal(operandVal[1]);
		}
	}
	else if (opc >= CLR_OC && opc <= PRN_OC) /* second group. gets 1 operand */
	{
		mw->destAddr = firstMode;
		
		if (firstMode == REGI_DIR_ADDR)
		{
			mw->destRegi = getRegiVal(operandVal[0]);
		}
	}

	return mw; /* return multiword */

} /* end createMultiWord */



/* --- data_word *build_data_word in his code anat remove delete */
/* creates a single word */
singleWord *createSingleWord (addressingModes aMode,  )
{
	


} /* end singleWord */




