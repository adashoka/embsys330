/************************************************************************************

Copyright (c) 2001-2021  University of Washington Extension.

Module Name:

    tasks.c

Module Description:

    The tasks that are executed by the test application.

************************************************************************************/
#include <stdarg.h>

#include "bsp.h"
#include "print.h"


#define BUFSIZE 256

/************************************************************************************

   Allocate the stacks for each task.
   The maximum of tasks the application can have is defined by OS_MAX_TASKS in os_cfg.h

************************************************************************************/

static OS_STK   Task1Stk[APP_CFG_TASK_START_STK_SIZE];
static OS_STK   Task2Stk[APP_CFG_TASK_START_STK_SIZE];
static OS_STK   Task3Stk[APP_CFG_TASK_START_STK_SIZE];


// Task prototypes
void TaskOne(void* pdata);
void TaskTwo(void* pdata);
void TaskThree(void* pdata);


// Useful functions
void PrintWithBuf(char *buf, int size, char *format, ...);


/************************************************************************************

   This task is the initial task running, started by main(). It starts
   the system tick timer and creates all the other tasks. Then it deletes itself.

************************************************************************************/
void StartupTask(void* pdata)
{
    char buf[BUFSIZE];
    PrintWithBuf(buf, BUFSIZE, "StartupTask: Begin\n");
    PrintWithBuf(buf, BUFSIZE, "StartupTask: Starting timer tick\n");

    // Start the system tick
    SetSysTick(OS_TICKS_PER_SEC);
    
    // Create the test tasks
    PrintWithBuf(buf, BUFSIZE, "StartupTask: Creating the 3 tasks\n");

    // The maximum of tasks the application can have is defined by OS_MAX_TASKS in os_cfg.h
    OSTaskCreate(TaskOne, (void*)0, &Task1Stk[APP_CFG_TASK_START_STK_SIZE-1], APP_TASK_TEST1_PRIO);
    OSTaskCreate(TaskTwo, (void*)0, &Task2Stk[APP_CFG_TASK_START_STK_SIZE-1], APP_TASK_TEST2_PRIO);
    OSTaskCreate(TaskThree, (void*)0, &Task3Stk[APP_CFG_TASK_START_STK_SIZE-1], APP_TASK_TEST3_PRIO);

    // Delete ourselves, letting the work be done in the new tasks.
    PrintWithBuf(buf, BUFSIZE, "StartupTask: deleting self\n");
	OSTaskDel(OS_PRIO_SELF);
}

/************************************************************************************

   TaskOne turns on the LED every 100 ticks.

************************************************************************************/
void TaskOne(void* pdata)
{
    char buf[BUFSIZE];
    PrintWithBuf(buf, BUFSIZE, "TaskOne: starting\n");

    while(1)
    {
    	OSTimeDly(100);
    	PrintWithBuf(buf, BUFSIZE, "TaskOne: Turn LED On\n");
        SetLED(OS_TRUE);
    }
}

/************************************************************************************

   TaskTwo waits 50 ticks, then turns off the LED every 100 ticks.

************************************************************************************/
void TaskTwo(void* pdata)
{
    char buf[BUFSIZE];
    PrintWithBuf(buf, BUFSIZE, "TaskTwo: starting\n");

    OSTimeDly(50);  // Delay starting to interleave the tasks.

    while(1)
    {
    	OSTimeDly(100);
    	PrintWithBuf(buf, BUFSIZE, "TaskTwo: Turn LED OFF\n");
        SetLED(OS_FALSE);
    }
}

/************************************************************************************

   TaskThree - Counts up

************************************************************************************/
void TaskThree(void* pdata)
{
    char buf[BUFSIZE];
    PrintWithBuf(buf, BUFSIZE, "TaskThree: starting\n");

    int count = 0;
    while(1)
    {
    	PrintWithBuf(buf, BUFSIZE, "TaskThree: count = %d\n", count++);
    	int i;
    	for(i=0;i<100000;i++); // pretend work
    }
}

/************************************************************************************

   Print a formated string with the given buffer.
   Each task should use its own buffer to prevent data corruption.

************************************************************************************/
void PrintWithBuf(char *buf, int size, char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buf, size, format, args);
    PrintString(buf);
    va_end(args);
}

