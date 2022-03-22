/*
 * globals.h
 *
 *  Created on: Mar 21, 2022
 *      Author: user
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

/* anat to say what it is */

/* anat data data */

#define ROW_LEN 80 /* Row Max Length */

#define IC_INIT_VAL 100 /* anat Instruction Counter initial value = 0100 */
#define DC_INIT_VAL 0 /* anat Data Counter initial value = 0000 */
#define MAX_OPERAND 2 /* for the code.h file i needed to add it */
/* icf = ic + dc
dcf = 4
icf = ic + dcf = 104

dcf = dcf + 3
icf = icf + dcf
icf = 104 + 7 */

/* --- registers  in his code anat remove delete */
/* General Registers r0-r15 and  anat N/A for not available/not found */
typedef enum registers
{
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	NA_REG = -1

} registers; /* --- reg in his code anat remove delete */


/* --- opcodes in his code anat remove delete */
/* 16 opcode commands and N/A anat opcode for not found */
typedef enum opcode
{
	/* OC = opcode command */

	/* first group - 2 operands */
	MOV_OC = 0,

	CMP_OC = 1,

	ADD_OC = 2, /* funct 10 */
	SUB_OC = 2, /* funct 11 */

	LEA_OC = 4,
	/* end first group */

	/* second group - 1 operand */
	CLR_OC = 5, /* funct 10 */
	NOT_OC = 5, /* funct 11 */
	INC_OC = 5, /* funct 12 */
	DEC_OC = 5, /* funct 13 */

	JMP_OC = 9, /* funct 10 */
	BNE_OC = 9, /* funct 11 */
	JSR_OC = 9, /* funct 12 */

	RED_OC = 12,

	PRN_OC = 13,
	/* end second group */

	/* third group - without operands */
	RTS_OC = 14,

	STOP_OC = 15,
	/* end third group */

	 NA_OC = -1
} opcode; /* --- opcode in his code as well anat remove delete */


/* --- funct in his code anat remove delete */
/* 9 funct commands and anat N/A funct for not found */
typedef enum funct
{
	/* relates to opcode 2 */
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,

	/* relates to opcode 5 */
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,

	/* relates to opcode 9 */
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12,

	/* NA anat */
	NA_FUNCT = 0
} funct; /* --- funct in his code as well anat remove delete */


/* --- addressing_types in his code anat remove delete */
/* addressing modes */
typedef enum addressingModes
{
	/* immediate # */
	IMME_ADDR = 0,

	/* direct */
	DIR_ADDR = 1,

	/* index [] */
	INDX_ADDR = 2,

	/* register direct */
	REGI_DIR_ADDR = 3,

	/* N/A addressing modes for not found */
	 NA_ADDR = -1
} addressingModes; /* --- addressing_type in his code anat remove delete */


/* --- instruction in his code anat remove delete */
/* Guidance Sentences Types */
typedef enum senteType
{
	/* sentence type (name) 1: .data */
	DATA_TYPE,

	/* sentence type (name) 2: .string */
	STR_TYPE,

	/* sentence type (name) 3: .entry */
	ENTRY_TYPE,

	/* sentence type (name) 4: .extern */
	EXTERN_TYPE,

	/* N/A not found */
	 NA_TYPE

	/* error */
	/* ERR_TYPE anat */
} senteType; /* --- instruction in his code anat remove delete */


/* --- data_word in his code anat remove delete */
/* machine code without operands - single word struct */
typedef struct singleWordStruct
{
	unsigned int OPC; /* opcode uses all 16 bits */

	unsigned int E: 1;
	unsigned int R: 1;
	unsigned int A: 1;
	/*unsigned int ARE: 3;  bitfield anat */

	unsigned int CONST: 1; /* anat char or int? /the 19th bit */

} singleWord; /* --- data_word in his code anat remove delete */


/* --- code_word in his code anat remove delete */
/* machine code with operands - multi word struct */
typedef struct multiWordStruct
{
	unsigned int destAddr: 2; /* destination addressing 2 bits */
	unsigned int destRegi: 4; /* destination register 4 bits */
	unsigned int srcAddr: 2; /* source addressing 2 bits */
	unsigned int srcRegi: 4; /* source register 4 bits */
	unsigned int funct: 4; /* funct 4 bits */
	unsigned int E: 1;
	unsigned int R: 1;
	unsigned int A: 1;
	/*unsigned int ARE: 3;  A R E 3 bits */
	unsigned int CONST: 1;  /* the 19th bit */

} multiWord; /* --- code_word in his code anat remove delete */


/* --- machine_word  in his code anat remove delete */
/* single word - multi word struct */
typedef struct finalMultiWordStruct
{
	short multiWordLen; /* multi word length */

	/* union is or single or multi. but in the multi we use the single anat */

	singleWord *sws;
	multiWord *mws;


} finalMultiWord; /* --- machine_word in his code anat remove delete */



/* --- machine_word  in his code anat remove delete */
/* single word - multi word struct */
typedef struct finalSingleWordStruct
{
	short singleWordLen; /* single word length. should be 0 anat */

	/* union is or single or multi. but in the multi we use the single anat */
	singleWord *sws;


} finalSingleWord; /* --- machine_word in his code anat remove delete */


/* --- line_info in his code anat remove delete */
/* new line */
typedef struct newLine
{
	long lineNum;  /* line number */
	char *fileName;
	char *data; /* file's data */
} newLine;

#endif /* GLOBALS_H_ */
