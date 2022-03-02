/**
    discoveryboard.h
    Board specific definitions live here
    Developed for University of Washington embedded systems programming certificate
    
    2021/1 Nick Strathy wrote/arranged it

*/
#ifndef __DISCOVERYBOARD_H
#define __DISCOVERYBOARD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"

// User button
//#define GPIO_PIN_USER_BUTTON    LL_GPIO_PIN_13
//#define GPIO_PORT_USER_BUTTON   GPIOC

// User LED
#define GPIO_PIN_USER_LED            LL_GPIO_PIN_14
#define GPIO_PORT_USER_LED           GPIOB
#define USER_LED_CLK_ENABLE          LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)

// USART GPIO
#define GPIO_TX_AF_SOURCE       LL_GPIO_PIN_6
#define GPIO_RX_AF_SOURCE       LL_GPIO_PIN_7
#define GPIO_USART_AF           GPIO_AF_USART1
#define GPIO_PIN_TX             LL_GPIO_PIN_6
#define GPIO_PIN_RX             LL_GPIO_PIN_7
#define GPIO_PORT_USART         GPIOA

// USART 
#define COMM                    USART1

#endif