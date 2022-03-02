/*
    bspLed.c

    Board support for controlling LEDs

    Developed for University of Washington embedded systems programming certificate
    
    2020/8 Nick Strathy wrote/arranged it for STM332L475
*/

#include "bsp.h"

void LedInit()
{
  /* Enable the USER LED Clock */
  USER_LED_CLK_ENABLE;

  /* Configure IO in output push-pull mode to drive external LED2 */
  LL_GPIO_SetPinMode(GPIO_PORT_USER_LED, GPIO_PIN_USER_LED, LL_GPIO_MODE_OUTPUT);
}

void SetLED(uint32_t On)
{
    if (On) {
        LL_GPIO_SetOutputPin(GPIO_PORT_USER_LED, GPIO_PIN_USER_LED);
      } else {
        /* The high 16 bits of BSRR reset the pin */
        LL_GPIO_ResetOutputPin(GPIO_PORT_USER_LED, GPIO_PIN_USER_LED);
     }
}
