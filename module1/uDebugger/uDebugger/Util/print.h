/**********************************************************
FILE NAME  	: print.h
DESCRIPTION     : 
Copyright	: David Allegre
		: 2015
		: All Rights Reserved
**********************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PRINT_H
#define __PRINT_H

/* Includes ------------------------------------------------------------------*/
#include "discoveryboard.h"
#include <stdio.h>

/* Exported functions ------------------------------------------------------- */
void PrintHex(uint32_t u32);
void Print_uint32(uint32_t u);
void PrintByte(char c);
void PrintString(char *ptr);


/* Macros ------------------------------------------------------------------- 
 * Macros for printing debug messages.
 * Credit goes to Mitch Ishihara and prior instructors for this code
*/
extern char stringbuffer[];
#define _DBG_PRINTX_ARG(arg...) arg /* unroll the parens around the var args*/
#define PRINTBUFMAX 256
#define RETAILMSG(x,y) \
    ((x) ? (snprintf(stringbuffer, PRINTBUFMAX, _DBG_PRINTX_ARG y), PrintString(stringbuffer)) : (void)(0))
#define PRINT_DEFINEBUFFER() char stringbuffer[PRINTBUFMAX]
#define PRINT_BUFFER() extern char stringbuffer[]

/* EOF ---------------------------------------------------------------------- */
#endif