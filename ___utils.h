/*
 * utils.h
 *
 *  Created on: Mar 21, 2022
 *      Author: user
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "globals.h"

/* anat add data here? */
int isWholeNum(char *valToCheck);

/* anat add data here? */
int isValidLbl (char *lblToCheck);

/* anat add data here? */
int isReserved (char *valToGet);

/* anat add data here? */
senteType getSenteTypeName (char *valToCheck);

/* anat add data here? */
void *tryToMalloc(long size);


#endif /* UTILS_H_ */
