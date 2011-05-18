/*
 * IncFile1.h
 *
 * Created: 09.05.2011 10:46:47
 *  Author: Huebener.Se
 */ 

#ifndef F_CPU
#error "F_CPU is undefined!"
#endif

#ifndef TEST1_H_
#define TEST1_H_

#define LED_RED_ON		PORTB &= ~(1 << PB2); PORTB |= (1 << PB1)
#define LED_GREEN_ON	PORTB &= ~(1 << PB1); PORTB |= (1 << PB2)
#define LED_OFF			PORTB &= ~((1 << PB1) | (1 << PB2))

void initGPIO(void);
void initTimer0(void);
void initTimer1(void);



#endif /* TEST1_H_ */