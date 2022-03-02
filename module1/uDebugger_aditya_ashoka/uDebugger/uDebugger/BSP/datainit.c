/**
 * datainit.c
 * Overlay the initialization data onto the RAM region that contains them
 * Zero initialize the bss section
 */
#include <stdint.h>

/*
 * a pragma is a compiler specific extension
 *  This pragma section extension is used to tell the linker the sections used in this file
 */
#pragma section = ".data_init"          /*  !< These are the values to assigned to the globals (in flash) */
#pragma section = ".data"               /* !< This is where the globals reside in RAM */
#pragma section = ".bss"                /* !< This is the zero-init area */


/**
  ** \brief Called before the data section is initialized, do
  ** not use any globals
  ** IAR linkers uses the "__section_begin" and "__section_end"  to populate the
  ** variable with the actual value at link time. Keil uses a similar method. GCC is completely different.
  ** This function is also set to the entry point in the ELF header. (see project->options->linker->library)
  **/
void InitializeDataSection(void)
{
    /**
     ** section_begin is an IAR helper to get information about sections. The linker
     **  populates the correct data
     **/
    uint8_t*   pInitDataSource = __section_begin(".data_init");
    uint8_t*   pInitDataTarget = __section_begin(".data");
    uint8_t*   pInitDataEnd    = __section_end(".data_init");
      
    /* Figure out how much data to copy */
    uint32_t    size = pInitDataEnd - pInitDataSource;

    /* Do the copy of the initialization values onto the RAM area */
    while (size--) {
      *pInitDataTarget++ = *pInitDataSource++;
    }   
    
    /* Zero initialized section is called bss, give it the same treatment */
    uint8_t* pZeroInit = __section_begin(".bss");
    uint8_t* pZeroInitEnd = __section_end(".bss");
    size = pZeroInitEnd - pZeroInit;
    while (size--) {
      *pZeroInit++ = 0;
    }       
}