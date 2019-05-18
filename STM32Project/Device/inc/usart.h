#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

#define USARTx_Clock        RCC_APB2Periph_USART1
#define USARTx_Port_Clock   RCC_APB2Periph_GPIOA
#define USARTx_GPIOx        GPIOA
#define USARTx_TX_Pin       GPIO_Pin_9
#define USARTx_RX_Pin       GPIO_Pin_10
#define USARTx_             USART1

void usart_Init(u32 bound);

#endif  /* __USART_H */

