#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <os_cpu.h>

void PrintHex(INT32U u32);
void Print_uint32(INT32U u);
void PrintString(char *ptr);


//
// Macros for printing debug messages.
//
#define _DBG_PRINTX_ARG(arg...) arg /* unroll the parens around the var args*/
#define RETAILMSG(x,y) \
    ((x) ? (snprintf(stringbuffer, PRINTBUFMAX, _DBG_PRINTX_ARG y), PrintString(stringbuffer)) : (void)(0))
#define PRINTBUFMAX 128
#define PRINT_DEFINEBUFFER() char stringbuffer[PRINTBUFMAX]
#define PRINT_BUFFER() extern char stringbuffer[]

#ifdef DEBUG
#define DEBUGMSG(x,y) \
    ((x) ? (snprintf(stringbuffer, PRINTBUFMAX, _DBG_PRINTX_ARG y), PrintString(stringbuffer)) : (void)(0))
#else // DEBUG
    #define DEBUGMSG(x,y) (0)
#endif // DEBUG

#endif /* __PRINT_H__ */
