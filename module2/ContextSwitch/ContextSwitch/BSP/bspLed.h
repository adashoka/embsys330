/*
    bspLed.h

    Board support for controlling LEDs

    Developed for University of Washington embedded systems programming certificate
    
    2020/8 Nick Strathy wrote/arranged it for STM32L475
*/

#ifndef __BSPLED_H
#define __BSPLED_H

void LedInit();
void SetLED(uint32_t On);

#endif /* __BSPLED_H */