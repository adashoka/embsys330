/*
    bspUart.h

    Board support for controlling UART interfaces

    Developed for University of Washington embedded systems programming certificate
    
    2016/2 Nick Strathy wrote/arranged it for NUCLEO-F401RE MCU
    2020/8 Nick Strathy wrote/arranged it for STM32L475
*/

#ifndef __BSPUART_H
#define __BSPUART_H

#define USARTx_INSTANCE               USART1
#define USARTx_CLKSOURCE              LL_RCC_USART2_CLKSOURCE
#define USARTx_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2)

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)   /* Enable the peripheral clock of GPIOB */
#define USARTx_TX_PIN                 LL_GPIO_PIN_6
#define USARTx_TX_GPIO_PORT           GPIOB
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_7
#define USARTx_RX_GPIO_PORT           GPIOB
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_7, LL_GPIO_AF_7)

// Application interface to hardware
void UartInit(uint32_t baud);
void PrintByte(char c);
char ReadByte();


#endif /* __BSPUART_H */