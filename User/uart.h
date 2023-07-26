/*_UART_H*/
#ifndef _UART_H_
#define _UART_H_

#include "debug.h"

#define TxSize1    (128)
#define TxSize2    (128)
#define size(a)    (sizeof(a) / sizeof(*(a)))

void MY_USART_Init(uint32_t baudrate);
void DMA_INIT(void);





















#endif /*_UART_H_*/
