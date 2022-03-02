/*******************************************************************************
FILE NAME   : print.c
DESCRIPTION : Very lightweight print functions.

HISTORY     :
2007/10/01  : Mitch Ishihara
2007/10/30  : Added Alan's uint32_t print
            : Added Stephane's printHex
2015/10/21  : David Allegre
            : Adapted routines for the Nucleo kit
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "print.h"
#include "bsp.h"

void PrintHex(uint32_t u32) {
uint32_t   u32Mask  = 0xF0000000;
uint8_t    u32Shift = 32;
uint32_t   u32Char;

  do {
    u32Shift -= 4;
    u32Char = (u32 & u32Mask) >> u32Shift;
    u32Mask >>= 4;
    if (u32Char >= 0xA) {
      PrintByte('A' + (u32Char - 10));
    } else {
      PrintByte('0' + u32Char);
    }
  } while (u32Shift > 0);
}

void Print_uint32(uint32_t u) {
char buffer[11];
char *p = &buffer[10];

    *p = '\0';
    do {
        p--;
        *p = (u % 10) + '0';
        u /= 10;
    } while (u > 0);

    PrintString(p);
}
//
void PrintString(char *ptr) {

  if (ptr==0 || *ptr==0) return;

  do {
    if (*ptr=='\n') {
      PrintByte(*ptr++);
      PrintByte('\r');
    } else {
      PrintByte(*ptr++);
    }
  } while (*ptr!=0);
}
