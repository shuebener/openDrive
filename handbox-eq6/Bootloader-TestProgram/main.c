/*
 * Bootloader_TestProgram.c
 *
 * Created: 18.05.2011 15:14:04
 *  Author: Huebener.Se
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

#include "main.h"
#include "myuart.h"

extern FILE UART0_STDOutHandler;


int main(void) {
	void (*bootloader)( void ) = 0x1800;
	stdout = &UART0_STDOutHandler;
	
	UART0_Init();
	
	printf("Main program now running...\n");
	sei(); //Enable Interrupts	
	
	uint8_t test=0;
    while(1) {
        test=1;
		bootloader();
    }
}