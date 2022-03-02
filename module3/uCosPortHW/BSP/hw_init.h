/*
*/
#ifndef __HW_INIT_H
#define __HW_INIT_H


// Application interface to hardware

#define BAUD_RATE 38400

void Hw_init(void);
void SetSysTick(uint32_t ticksPerSec);

#endif /* __HW_INIT_H */