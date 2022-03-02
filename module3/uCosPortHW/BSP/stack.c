#include "stack.h"

/*
	Initialize the given stack with values that will be popped into the 
    registers when the given task code starts up.

    stack: pointer to the lower boundary address of a stack

    task_address: address of the start of code for a task
*/
uint32_t initialize_stack(uint32_t* stack, void* task_address)
{
	// The stacking convention is that the stack grows downwards in memory (addresses
    // grow smaller) so we want to start by calculating the initial top of the stack.
	uint32_t *stkptr = (uint32_t*)(stack + STACKSIZE - 1);
    
    // We mimic the stack frame saved by hardware for an exception.
    // xPSR and PC are the only registers that get special values.
    // The rest of the registers (R0-R3, R12, R14) get "don't-care" values 
    // however to aid future troubleshooting we give them "water mark" values.
    *(--stkptr) = 0x01000000uL;                          // xPSR
    *(--stkptr) = (uint32_t)task_address;                // Entry Point of task code
    *(--stkptr) = 0x14141414uL;                          // R14 (LR) Reminder: the task code should never return
    *(--stkptr) = 0x12121212uL;                          // R12
    *(--stkptr) = 0x03030303uL;                          // R3
    *(--stkptr) = 0x02020202uL;                          // R2
    *(--stkptr) = 0x01010101uL;                          // R1
    *(--stkptr) = 0x00000000uL;                          // R0

    // Now set up the remaining registers
    *(--stkptr) = 0x11111111uL;                          // R11
    *(--stkptr) = 0x10101010uL;                          // R10
    *(--stkptr) = 0x09090909uL;                          // R9
    *(--stkptr) = 0x08080808uL;                          // R8
    *(--stkptr) = 0x07070707uL;                          // R7
    *(--stkptr) = 0x06060606uL;                          // R6
    *(--stkptr) = 0x05050505uL;                          // R5
    *(--stkptr) = 0x04040404uL;                          // R4

    // Anything missing? What about R13 (SP)? Consider why we don't save it
    // on the stack.
    
	return (uint32_t)(stkptr);
}

