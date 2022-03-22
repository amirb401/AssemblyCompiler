
#ifndef CODE_H_
#define CODE_H_

#include "globals.h"
#include "utils.h" /* should we have it here? */

/* anat add data here? */
void getOppOCFun (char *oppr, opcode *destOpc, funct *destFunc);

/* anat add data here? */
addressingModes getAddressMode (char *operandVal);

/* anat add data here? */
registers getRegiVal (char *valToGet);

/* anat add data here? */
int opcodeGroupsCheck (opcode opc, int countOC);

/* anat add data here? */
multiWord *createMultiWord (opcode opc, funct fnc, int countOC, char *operandVal[MAX_OPERAND]);


#endif /* CODE_H_ */
