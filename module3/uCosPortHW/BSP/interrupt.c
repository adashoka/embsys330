
#include "bsp.h"


void SysTick_Handler(void)
{
  // switch context by triggering PendSV exception
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; // Set PendSV to pending
}


