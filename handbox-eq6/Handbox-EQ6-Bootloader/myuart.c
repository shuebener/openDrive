/*
 * uart.c
 *
 * Created: 10.05.2011 15:02:58
 *  Author: Huebener.Se
 */ 

#ifndef NOSTDOUT
#include <stdio.h>
#include <stdlib.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h> 

#include "myuart.h"


volatile struct {
	char data[UART_RX_BUFFER_SIZE];
	uint8_t read;
	uint8_t write;
} UART_RXBuffer = {{}, 0, 0};
	
volatile struct {
	char data[UART_TX_BUFFER_SIZE];
	uint8_t read;
	uint8_t write;
} UART_TXBuffer = {{}, 0, 0};

#ifndef NOSTDOUT
//stdout handler for printf...
volatile FILE UART0_STDOutHandler = FDEV_SETUP_STREAM(UART0_SendCharSTDOUT, NULL, _FDEV_SETUP_WRITE );	
#endif
	

 void UART0_Init(void) {
	
	//USART Baud Rate Registers
	UBRR0H = (uint8_t) (UART_UBRR0 >> 8);
	UBRR0L = (uint8_t) (UART_UBRR0 & 0xFF);		
	
	//USART Control and Status Register 0 A
	UCSR0A = (0 << RXC0)		//USART Receive Complete
	       | (0 << TXC0)		//USART Transmit Complete
		   | (0 << UDRE0)		//USART Data Register Empty
		   | (0 << FE0)			//Frame Error
		   | (0 << DOR0)		//Data OverRun
		   | (0 << UPE0)		//USART Parity Error
		   | (1 << U2X0)		//Double the USART Transmission Speed
		   | (0 << MPCM0);		//Multi-processor Communication Mode
		   
	//USART Control and Status Register 0 C
	UCSR0C = (0b00 << UMSEL00)	//USART Mode Select: Asynchronous USART
		   | (0b00 << UPM00)	//Parity Mode: Disabled
		   | (0 << USBS0)		//Stop Bit Select: 1bit
		   | (0b11 << UCSZ00)	//Character Size (see B): 8bit
		   | (0 << UCPOL0);		//Clock Polarity	   
	
	//USART Control and Status Register 0 B
	UCSR0B = (1 << RXCIE0)		//RX Complete Interrupt Enable
	       | (0 << TXCIE0)		//TX Complete Interrupt Enable
		   | (0 << UDRIE0)		//USART Data Register Empty Interrupt Enable
		   | (1 << RXEN0)		//Receiver Enable
		   | (1 << TXEN0)		//Transmitter Enable
		   | (0 << UCSZ02)		//Character Size (see C)
		   | (0 << RXB80)		//Receive Data Bit 8
		   | (0 << TXB80);		//Transmit Data Bit 8		 
	
	return;
}

#ifndef NOSTDOUT
int UART0_SendCharSTDOUT(char sendchar, FILE *stream) {	
	UART0_SendChar(sendchar);	 
	return 0;
}
#endif

void UART0_SendChar(char sendchar) {
	
	//Daten in den TX-Buffer schreiben...
	uint8_t next = ((UART_TXBuffer.write + 1) & UART_TX_BUFFER_MASK);
	while(UART_TXBuffer.read == next) {} //wait for free space in buffer..	
	
	UART_TXBuffer.data[UART_TXBuffer.write] = sendchar;
	UART_TXBuffer.write = next;	
		
	//Interrupt aktivieren
	UCSR0B |= (1 << UDRIE0); //USART Data Register Empty Interrupt Enable	
	 
	return;
}

void UART0_SendString(char *string) {
    while (*string) {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen" */
        UART0_SendChar(*string);
        string++;
    }	
}


//USART, UDR Empty Handler
ISR(USART_UDRE_vect) {

	if (UART_TXBuffer.read == UART_TXBuffer.write) {
		//buffer empty -> deactivate interrupt
		UCSR0B &= ~(1 << UDRIE0);
	} else {	
		//write buffered data to UDR		
		UDR0 = UART_TXBuffer.data[UART_TXBuffer.read];
		UART_TXBuffer.read = (UART_TXBuffer.read+1) & UART_TX_BUFFER_MASK;	
	}	
	
	return;	
}

//USART, RX Complete Handler
ISR(USART_RX_vect) {

	uint8_t xxx;
	uint8_t status = UCSR0A;
	char receivedchar = UDR0;
	
	//Frame Error
	if(status & (1<<FE0)) {
		xxx=1;
	}	
	
	//Data OverRun
	if(status & (1<<DOR0)) {
		xxx=2;
	}
		
	//USART Parity Error
	if(status & (1<<UPE0)) {
		xxx=3;
	}

	//Daten in den RX-Buffer schreiben...
	uint8_t next = ((UART_RXBuffer.write + 1) & UART_RX_BUFFER_MASK);
	while(UART_RXBuffer.read == next) {} //wait for free space in buffer..	
	
	UART_RXBuffer.data[UART_RXBuffer.write] = receivedchar;
	UART_RXBuffer.write = next;	

	return;	
}
