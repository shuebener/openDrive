/*
 * Test1.c
 *
 * Created: 09.05.2011 10:35:33
 *  Author: Huebener.Se
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

#include "main.h"
#include "myuart.h"
#include "switch.h"
#include "button.h"
extern FILE UART0_STDOutHandler;

volatile uint32_t Timer0_CNT = 0;
volatile uint32_t Timer1_CNT = 0; //5ms TickRate


int main(void) {	
	stdout = &UART0_STDOutHandler;
	uint32_t tmp_cnt1=-1, tmp_cnt2=0;
	uint8_t tgl=0;
	
	initGPIO();
	//initTimer0();
	initTimer1();
	UART0_Init();
	
	printf("Controller initialized...\n");
	sei(); //Enable Interrupts
	
	while(1) {		
		
		
		if(tmp_cnt1!=Timer1_CNT && !(Timer1_CNT%2)) {
			//Check every 2x5ms for changed input pins (incl. debouncing)
			tmp_cnt1=Timer1_CNT;	
			Switch_Update();
			Button_Update();
		}
		
		//Check for changed buttons
		Button_CheckForAction();
		


		if(tmp_cnt2 != Timer1_CNT && !(Timer1_CNT%10)) {
			tmp_cnt2=Timer1_CNT;
			//10x5ms TickRate...
			
			if(!tgl) {
				printf("Ping\n");
				tgl=1;
			} else {
				printf("Pong\n");
				tgl=0;
			}			
			
		}		
		
		
		
		
		if(Timer1_CNT >= 60000) {Timer1_CNT=0;}
	}
	return 0;
}


void initGPIO(void) {
	
	
	//Port x Data Direction Register
	//(1 = Output / 0 = Input)
	DDRB = (1 << PB0)	//<unused> => output
	     | (1 << PB1)	//LED_GREEN => output
		 | (1 << PB2)	//LED_RED => output
		 | (1 << PB3)	//<unused> => output
		 | (1 << PB4)	//<unused> => output
		 | (1 << PB5)	//<unused> => output
		 | (1 << PB6)	//<unused> => output
		 | (1 << PB7);	//<unused> => output
		 
	DDRC = (0 << PC0)	//REV_DEC => input (switch)
	     | (0 << PC1)	//REV_RA => input (switch)
		 | (0 << PC2)	//RA+ => input (button)
		 | (0 << PC3)	//RA- => input (button)
		 | (0 << PC4)	//DEC+ => input (button)
		 | (0 << PC5)	//DEC- => input (button)
		 | (1 << PC6);	//<unused> => output
		 
	DDRD = (0 << PD0)	//UART_RXD => input
	     | (1 << PD1)	//UART_TXD => output
		 | (1 << PD2)	//<unused> => output
		 | (0 << PD3)	//HEM_N => input (switch)
		 | (0 << PD4)	//HEM_S => input (switch)
		 | (0 << PD5)	//SPEED_2X => input (switch)
		 | (0 << PD6)	//SPEED_8X => input (switch)
		 | (0 << PD7);	//SPEED_16X => input (switch)
	
	
	
	//Port x Data Register
	//Input: PullUp On/Off
	//Output: Port On/Off		
	PORTB = (0 << PB0)	//<unused> => output => Off
	      | (0 << PB1)	//LED_GREEN => output => Off
		  | (0 << PB2)	//LED_RED => output => Off
		  | (0 << PB3)	//<unused> => output => Off
		  | (0 << PB4)	//<unused> => output => Off
		  | (0 << PB5)	//<unused> => output => Off
		  | (0 << PB6)	//<unused> => output => Off
		  | (0 << PB7);	//<unused> => output => Off
		 
	PORTC = (1 << PC0)	//REV_DEC => input (switch) => PullUp on
	      | (1 << PC1)	//REV_RA => input (switch) => PullUp on
		  | (1 << PC2)	//RA+ => input (button) => PullUp on
		  | (1 << PC3)	//RA- => input (button) => PullUp on
		  | (1 << PC4)	//DEC+ => input (button) => PullUp on
		  | (1 << PC5)	//DEC- => input (button) => PullUp on
		  | (0 << PC6);	//<unused> => output => Off
		 
	PORTD = (1 << PD0)	//UART_RXD => input => PullUp on
	      | (0 << PD1)	//UART_TXD => output => Off
		  | (0 << PD2)	//<unused> => output => Off
		  | (1 << PD3)	//HEM_N => input (switch) => PullUp on
		  | (1 << PD4)	//HEM_S => input (switch) => PullUp on
		  | (1 << PD5)	//SPEED_2X => input (switch) => PullUp on
		  | (1 << PD6)	//SPEED_8X => input (switch) => PullUp on
		  | (1 << PD7);	//SPEED_16X => input (switch) => PullUp on
		
	return;
}

void initTimer0(void) {
	
	//Timer/Counter Interrupt Mask Register
	TIMSK0 = (0 << OCIE0B)		//Output Compare Match B Interrupt Enable
	       | (0 << OCIE0A)		//Output Compare Match A Interrupt Enable
		   | (1 << TOIE0);		//Overflow Interrupt Enable	
	
	//Timer/Counter Control Register A
	TCCR0A = (0b00 << COM0A0)	//Compare Match Output A Mode: Normal port operation, OC0A disconnected.
		   | (0b00 << COM0B0)	//Compare Match Output B Mode: Normal port operation, OC0B disconnected.
		   | (0b00 << WGM00);	//Waveform Generation Mode: normal
	
	//Timer/Counter Control Register B
	TCCR0B = (0 << FOC0A)		//Force Output Compare A
	       | (0 << FOC0B)		//Force Output Compare B
		   | (0 << WGM02)		//Waveform Generation Mode: normal
		   | (0b001 << CS00);	//Clock Select: CLK


	return;
}


void initTimer1(void) {
	
	//Output Compare Register 1 A
	uint16_t ocr = (F_CPU / 200) - 1; //5ms TickRate
	OCR1AH = (uint8_t) (ocr >> 8);
	OCR1AL = (uint8_t) (ocr & 0xFF);
	
	//Timer/Counter1 Interrupt Mask Register
	TIMSK1 = (0 << ICIE1)		//Input Capture Interrupt Enable
	       | (0 << OCIE1B)		//Output Compare B Match Interrupt Enable
		   | (1 << OCIE1A)		//Output Compare A Match Interrupt Enable
		   | (0 << TOIE1);		//Overflow Interrupt Enable	
	
	//Timer/Counter1 Control Register A
	TCCR1A = (0b10 << COM1A0)	//Compare Output Mode for Channel A: Clear on Compare Match
	       | (0b00 << COM1B0)	//Compare Output Mode for Channel B: Normal port operation
		   | (0b00 << WGM10);	//Waveform Generation Mode
		   
	//Timer/Counter1 Control Register B
	TCCR1B = (0 << ICNC1)		//Input Capture Noise Canceler
	       | (0 << ICES1)		//Input Capture Edge Select
		   | (0b01 << WGM12)	//Waveform Generation Mode
		   | (0b001 << CS10);	//Clock Select

/*		   
	//Timer/Counter1 Control Register C
	TCCR1C = (0 << FOC1A)		//Force Output Compare for Channel A
	       | (0 << FOC1B);		//Force Output Compare for Channel B
*/
	
	
	return;
}


//Timer0 Overflow Interrupt
ISR(TIMER0_OVF_vect) {
	Timer0_CNT++;	
}

//Timer1 Compare Match Interrupt
ISR(TIMER1_COMPA_vect) {
	Timer1_CNT++;
}