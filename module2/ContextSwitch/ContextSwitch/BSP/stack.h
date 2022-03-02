#ifndef __STACK_H
#define __STACK_H

#include <stdint.h>

// Application interface to hardware

// Number of entries in stack. Each entry is a uint32_t
#define STACKSIZE 256

uint32_t initialize_stack(uint32_t* stack, void* task_address);

#endif /* __STACK_H */