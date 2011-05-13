/*
 * action.c
 *
 * Created: 13.05.2011 13:22:58
 *  Author: Huebener.Se
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

#include "action.h"
#include "myuart.h"
#include "button.h"
#include "switch.h"

extern FILE UART0_STDOutHandler;

void Action_RApButtonPressed(void) {	
	printf("Action_RApButtonPressed\n");
	
	return;
}

void Action_RApButtonUnpressed(void) {
	printf("Action_RApButtonUnpressed\n");
	
	return;
}

void Action_RAmButtonPressed(void) {
	printf("Action_RAmButtonPressed\n");
	
	return;
}

void Action_RAmButtonUnpressed(void) {
	printf("Action_RAmButtonUnpressed\n");
	
	return;
}

void Action_DECpButtonPressed(void) {
	printf("Action_DECpButtonPressed\n");
	
	return;
}

void Action_DECpButtonUnpressed(void) {
	printf("Action_DECpButtonUnpressed\n");
	
	return;
}

void Action_DECmButtonPressed(void) {
	
	return;
}

void Action_DECmButtonUnpressed(void) {
	
	return;
}


void SendCmd(char CMD[21], char Value[6]) {
	
	printf(":oD%s%s#", CMD, Value);
	return;
}


void getSpeed(uint8_t SS_Speed, char Speed[]) {
	switch(SS_Speed) {
		case SWITCH_SS_SPEED_2X:	strcpy(Speed, "2"); break;
		case SWITCH_SS_SPEED_8X:	strcpy(Speed, "8"); break;
		case SWITCH_SS_SPEED_16X:	strcpy(Speed, "16"); break;
		default:					strcpy(Speed, "1"); break;
	}
	
	return;
}