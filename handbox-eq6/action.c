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

#include "main.h"
#include "action.h"
#include "myuart.h"
#include "button.h"
#include "switch.h"

extern FILE UART0_STDOutHandler;
extern SWITCH_STATUS_t Switch_Status;

void Action_RApButtonPressed(void) {	
	LED_GREEN_ON;

	if(Switch_Status.Hemisphere == SWITCH_SS_HEM_N) {SendCmd("SetHemisphere","North");}
	else {SendCmd("SetHemisphere","South");}

	if(Switch_Status.Reverse_Ra) {SendCmd("SetReverseRa","On");}
	else {SendCmd("SetReverseRa","Off");}
	
	char Speed[6];
	getSpeed(Switch_Status.Speed, Speed);
	SendCmd("SetSpeed",Speed);
	
	SendCmd("Ra_P_Start","");
	return;
}

void Action_RApButtonUnpressed(void) {
	SendCmd("RaStop","");
	LED_RED_ON;
	return;
}

void Action_RAmButtonPressed(void) {
	LED_GREEN_ON;
	
	if(Switch_Status.Hemisphere == SWITCH_SS_HEM_N) {SendCmd("SetHemisphere","North");}
	else {SendCmd("SetHemisphere","South");}

	if(Switch_Status.Reverse_Ra) {SendCmd("SetReverseRa","On");}
	else {SendCmd("SetReverseRa","Off");}
	
	char Speed[6];
	getSpeed(Switch_Status.Speed, Speed);
	SendCmd("SetSpeed",Speed);
	
	SendCmd("Ra_M_Start","");
	return;
}

void Action_RAmButtonUnpressed(void) {
	SendCmd("RaStop","");
	LED_RED_ON;
	return;
}

void Action_DECpButtonPressed(void) {
	LED_GREEN_ON;

	if(Switch_Status.Hemisphere == SWITCH_SS_HEM_N) {SendCmd("SetHemisphere","North");}
	else {SendCmd("SetHemisphere","South");}

	if(Switch_Status.Reverse_Ra) {SendCmd("SetReverseRa","On");}
	else {SendCmd("SetReverseRa","Off");}
	
	char Speed[6];
	getSpeed(Switch_Status.Speed, Speed);
	SendCmd("SetSpeed",Speed);
	
	SendCmd("Dec_P_Start","");
	return;
}

void Action_DECpButtonUnpressed(void) {
	SendCmd("DecStop","");
	LED_RED_ON;
	return;
}

void Action_DECmButtonPressed(void) {
	LED_GREEN_ON;

	if(Switch_Status.Hemisphere == SWITCH_SS_HEM_N) {SendCmd("SetHemisphere","North");}
	else {SendCmd("SetHemisphere","South");}

	if(Switch_Status.Reverse_Ra) {SendCmd("SetReverseRa","On");}
	else {SendCmd("SetReverseRa","Off");}
	
	char Speed[6];
	getSpeed(Switch_Status.Speed, Speed);
	SendCmd("SetSpeed",Speed);
	
	SendCmd("Dec_M_Start","");
	return;
}

void Action_DECmButtonUnpressed(void) {
	SendCmd("DecStop","");
	LED_RED_ON;
	return;
}


void Action_ShowSwitchStatus(void) {
/*
typedef struct {
	uint8_t Speed;			//0 = 2x; 1 = 8x; 2 = 16x
	uint8_t Hemisphere;		//0 = North; 1 = South
	uint8_t Reverse_Ra;		//0 = Off; 1 = On
	uint8_t Reverse_Dec;	//0 = Off; 1 = On
} SWITCH_STATUS_t;
*/	

	printf("Speed: %d\nHemisphere: %d\nReverse_Ra: %d\nReverse_Dec: %d\n", Switch_Status.Speed, Switch_Status.Hemisphere, Switch_Status.Reverse_Ra, Switch_Status.Reverse_Dec);
	

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