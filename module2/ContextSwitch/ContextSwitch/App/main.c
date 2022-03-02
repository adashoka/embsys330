/*
 * University of Washington
 * Certificate in Embedded and Real-Time Systems
 *
 * Context Switch Homework
 */


#include "bsp.h"
#include "print.h"
#include "stack.h"

char clr_scrn[] = { 27, 91, 50, 74, 0 };              // esc[2J
/* Public variables ----------------------------------------------------------*/
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/
void delay(uint32_t time);


// Allocate space for two task stacks
uint32_t stackOne[STACKSIZE] = {9};
uint32_t stackTwo[STACKSIZE];


// To manage the contexts of two tasks we need to keep track of
// a separate stack for each task. The context of the task will 
// be stored in its stack.
//
// taskID is a global variable that holds the ID of the currently running task.
//
// currentSP is a global variable that holds the value of the
// stack pointer for the currently running task.

uint32_t stackOneSP;       // Value of task 1's stack pointer
uint32_t stackTwoSP;       // Value of task 2's stack pointer

uint32_t currentSP;        // The value of the current task's stack pointer
uint32_t taskID;           // The ID of the current task
uint32_t lock;


//
// taskOne counts up from 0.
// Never exits.
// <<aa: has complete control control of CPU cycles>>
void taskOne(void)
{
	int count = 0;
	while(1)
	{
		PrintString("task one: ");
		Print_uint32(count++);
		PrintString("\n");
		int i;
		for(i=0;i<100000;i++);    // delay
	}
}

//
// taskTwo counts down from 0xFFFFFFFF
// Never exits.
//
void taskTwo(void)
{
	int count = 0xFFFFFFFF;
	while(1)
	{
		PrintString("task two: ");
		Print_uint32(count--);
		PrintString("\n");
		int i;
		for(i=0;i<100000;i++);    // delay
	}
}

/*
	The task scheduler decides which task to run next.

	It alternates back and forth between the two tasks by changing the
	value of currentSP used by TaskSwitch in switch.s

	TaskSwitch does the real context switching work.

    sp: the top-of-stack pointer of the current task
*/
void scheduler(uint32_t sp)
{
	//PrintString("\nSwitch\n");

	if (taskID == 1)
	{
		stackOneSP = sp;               // Store stack pointer for task 1
		taskID = 2;                    // Set the taskID to task 2
		currentSP = stackTwoSP;        // Set the current stack pointer to task 2's stack pointer
	}
	else
	{
		stackTwoSP = sp;               // Store stack pointer for task 2
		taskID = 1;                    // Set the taskID to task 1
		currentSP = stackOneSP;        // Set the current stack pointer to task 1's stack pointer
	}
}


void main() {
    Hw_init();
    
    PrintString("University of Washington - Context Switch Application \n");  
 
    // Setup initial stack for taskTwo
    stackTwoSP = initialize_stack(stackTwo, (void*)taskTwo);


    // Make Task One the current task and begin executing it
    taskID = 1;
    taskOne();  // Should never return
    
    while(1);  // Should not arrive here
    
}

 