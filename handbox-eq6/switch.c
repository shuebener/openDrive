/*
 * switch.c
 *
 * Created: 12.05.2011 11:18:46
 *  Author: Huebener.Se
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

#include "switch.h"

SWITCH_STATUS_t Switch_Status = SWITCH_STATUS_DEFAULT;


void Switch_Update() {
	static SWITCH_STATUS_t Switch_StatusTMP = SWITCH_STATUS_DEFAULT;
	uint8_t test;
	
	//REV_DEC (low-active)
	if( PINC & (1<<PINC0) ) {
		//Switch Off
		if(Switch_StatusTMP.Reverse_Dec == SWITCH_SS_REVDEC_OFF) {
			//Switch Off for the second time...
			Switch_Status.Reverse_Dec = SWITCH_SS_REVDEC_OFF;	
		} else {
			//Switch Off for the first time...
			Switch_StatusTMP.Reverse_Dec = SWITCH_SS_REVDEC_OFF;
		}
	} else {
		//Switch On
		if(Switch_StatusTMP.Reverse_Dec == SWITCH_SS_REVDEC_ON) {
			//Switch On for the second time...
			Switch_Status.Reverse_Dec = SWITCH_SS_REVDEC_ON;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Reverse_Dec = SWITCH_SS_REVDEC_ON;
		}		
	}
	
	//REV_RA (low-active)
	if( PINC & (1<<PINC1) ) {
		//Switch Off
		if(Switch_StatusTMP.Reverse_Ra == SWITCH_SS_REVRA_OFF) {
			//Switch Off for the second time...
			Switch_Status.Reverse_Ra = SWITCH_SS_REVRA_OFF;	
		} else {
			//Switch Off for the first time...
			Switch_StatusTMP.Reverse_Ra = SWITCH_SS_REVDEC_OFF;
		}
	} else {
		//Switch On
		if(Switch_StatusTMP.Reverse_Ra == SWITCH_SS_REVRA_ON) {
			//Switch On for the second time...
			Switch_Status.Reverse_Ra = SWITCH_SS_REVRA_ON;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Reverse_Ra = SWITCH_SS_REVRA_ON;
		}		
	}	
	
	//Hemisphere (toggles between north & south)
	if( (PIND & (1<<PIND3)) && !(PIND & (1<<PIND4))) {
		//North
		if(Switch_StatusTMP.Hemisphere == SWITCH_SS_HEM_N) {
			//Switch On for the second time...
			Switch_Status.Hemisphere = SWITCH_SS_HEM_N;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Hemisphere = SWITCH_SS_HEM_N;
		}
	}
	else if( (PIND & (1<<PIND4)) && !(PIND & (1<<PIND3))) {
		//South
		if(Switch_StatusTMP.Hemisphere == SWITCH_SS_HEM_S) {
			//Switch On for the second time...
			Switch_Status.Hemisphere = SWITCH_SS_HEM_S;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Hemisphere = SWITCH_SS_HEM_S;
		}
	}	
	
	
	//Speed (toggles between 2x, 8x & 16x)
	if( (PIND & (1<<PIND5)) && !(PIND & (1<<PIND6)) && !(PIND & (1<<PIND7))) {
		//2x speed
		if(Switch_StatusTMP.Speed == SWITCH_SS_SPEED_2X) {
			//Switch On for the second time...
			Switch_Status.Speed = SWITCH_SS_SPEED_2X;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Speed = SWITCH_SS_SPEED_2X;
		}
	}
	else if( (PIND & (1<<PIND6)) && !(PIND & (1<<PIND5)) && !(PIND & (1<<PIND7))) {
		//8x speed
		if(Switch_StatusTMP.Speed == SWITCH_SS_SPEED_8X) {
			//Switch On for the second time...
			Switch_Status.Speed = SWITCH_SS_SPEED_8X;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Speed = SWITCH_SS_SPEED_8X;
		}
	}
	else if( (PIND & (1<<PIND7)) && !(PIND & (1<<PIND5)) && !(PIND & (1<<PIND6))) {
		//16x speed
		if(Switch_StatusTMP.Speed == SWITCH_SS_SPEED_16X) {
			//Switch On for the second time...
			Switch_Status.Speed = SWITCH_SS_SPEED_16X;	
		} else {
			//Switch On for the first time...
			Switch_StatusTMP.Speed = SWITCH_SS_SPEED_16X;
		}
	}
	
	
	return;	
}