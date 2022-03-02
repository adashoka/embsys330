/************************************************************************************

Copyright (c) 2001-2021  University of Washington Extension.  All rights reserved.

Module Name:

    main.c

Module Description:

    Test application for UCOS-II port.
	Ported from the UCOS test app.

Revision History:
Adapted for Cortex-M4 1/1/2016

************************************************************************************/


#include "bsp.h"
#include "print.h"
 

// Prototype for startup task
void StartupTask(void* pdata);

// Allocate a stack for the startup task
static OS_STK StartupStk[APP_CFG_TASK_START_STK_SIZE];

// Allocate the print buffer
PRINT_DEFINEBUFFER();


/************************************************************************************

Routine Description:

    Standard program main entry point.

Arguments:

    None.

Return Value:

    none.

************************************************************************************/
void main() {
INT8U err;
    Hw_init();
    
    RETAILMSG(1, ("uCOS Demo: Built %s %s.\r\n\r\n",
        __DATE__,
        __TIME__));  


    // Initialize the OS
    DEBUGMSG(1, ("main: Running OSInit()...\n"));

    OSInit();

    // Create the startup task
    DEBUGMSG(1, ("main: Creating start up task.\n"));

    err = OSTaskCreate(
        StartupTask,
        (void*)0,
        &StartupStk[APP_CFG_TASK_START_STK_SIZE-1],
        APP_TASK_START_PRIO);

    if (err != OS_ERR_NONE) {
        DEBUGMSG(1, ("main: failed creating start up task: %d\n", err));
        while(OS_TRUE);  //park on error
    }

    DEBUGMSG(1, ("Starting multi-tasking.\n"));

    // start the OS
    OSStart();
    
    DEBUGMSG(1, ("adityaaaa\n"));
    // should never reach here
    while (1);
}


  