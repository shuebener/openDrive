/*
 * Handbox_EQ6_Bootloader.c
 *
 * Created: 18.05.2011 11:57:56
 *  Author: Huebener.Se
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "main.h"

int main(void) {
    unsigned int 	c=0;				/* Empfangenes Zeichen + Statuscode */
    unsigned char	temp,				/* Variable */
                    flag=1,				/* Flag zum steuern der Endlosschleife */
					p_mode=0;			/* Flag zum steuern des Programmiermodus */
    void (*start)( void ) = 0x0000;     /* Funktionspointer auf 0x0000 */
 
    /* Interrupt Vektoren verbiegen */
    temp = MCUCR;
    MCUCR = temp | (1<<IVCE);
    MCUCR = temp | (1<<IVSEL);	
	
	
	sei();
	
    while(1) {
        
		
		flag=1;
		
    }
}