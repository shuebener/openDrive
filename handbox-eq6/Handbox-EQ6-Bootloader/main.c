/*
 * Handbox_EQ6_Bootloader.c
 *
 * Created: 18.05.2011 11:57:56
 *  Author: Huebener.Se
 */ 

//Linker!!!
//-Ttext=0x1800


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>

#include "main.h"
#include "myuart.h"

int main(void) {
	UART0_Init();	
    void (*start)( void ) = 0x0000;
 
    /* Interrupt Vektoren verbiegen */
    uint8_t temp = MCUCR;
    MCUCR = temp | (1<<IVCE);
    MCUCR = temp | (1<<IVSEL);	
	
	UART0_SendString("Bootloader started...\n");
	sei();
	
    while(1) {
        UART0_SendString("bl_running\n");

		for(uint32_t i=0; i<((F_CPU/10)*2); i++) {
			asm volatile ("nop");
		}
		
    }
}