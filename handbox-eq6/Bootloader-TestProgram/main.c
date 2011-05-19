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

#include <util/delay.h>

#include "main.h"
#include "myuart.h"

extern FILE UART0_STDOutHandler;


int main(void) {
	stdout = &UART0_STDOutHandler;
	UART0_Init();
	
	printf("Main program now running...\n");
	sei(); //Enable Interrupts	
	
    while(1) {
        printf("mp_running\n");
		_delay_ms(2000);
    }
}