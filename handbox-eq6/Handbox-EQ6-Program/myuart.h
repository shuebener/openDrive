/*
 * uart.h
 *
 * Created: 10.05.2011 15:02:18
 *  Author: Huebener.Se
 */ 

#ifndef F_CPU
#error "F_CPU is undefined!"
#endif

#ifndef MYUART_H_
#define MYUART_H_

/*** Settings ******************************************************************/
#define UART_UBRR0 0UL				//921.600baud (Error: 0,16%)
#define UART_RX_BUFFER_SIZE 64
#define UART_TX_BUFFER_SIZE 64
/*******************************************************************************/

#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE - 1)
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE - 1)

#define UART_NO_CHAR_AVAILABLE 1
#define UART_CHAR_AVAILABLE 0
#define UART_RX_ERROR_NOERROR 0
#define UART_RX_ERROR_FRAMEERROR 1
#define UART_RX_ERROR_DATAOVERRUN 2
#define UART_RX_ERROR_PARITYERROR 3
#define UART_RX_ERROR_FIFOOVERRUN 4


void UART0_Init(void);
void UART0_SendChar(char sendchar);
void UART0_SendString(char *string);
uint8_t UART0_ReadChar(char *readchar);

#ifndef UART_NOSTDLIB
int UART0_SendCharSTDOUT(char sendchar, FILE *stream);
#endif






#if (UART_RX_BUFFER_SIZE & UART_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#if (UART_TX_BUFFER_SIZE & UART_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

#endif /* MYUART_H_ */