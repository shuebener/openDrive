/*
 * button.c
 *
 * Created: 12.05.2011 15:38:08
 *  Author: Huebener.Se
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

#include "button.h"
#include "action.h"


BUTTON_STATUS_t Button_Status = BUTTON_STATUS_DEFAULT;

void Button_Update(void) {
	static BUTTON_STATUS_t Button_Status_TMP = BUTTON_STATUS_DEFAULT;	
	
	//RA+ (low-active)
	if( PINC & (1<<PINC3) ) {
		//Button Off
		if(Button_Status_TMP.RAp == BUTTON_OFF) {
			//Button Off for the second time...
			if(Button_Status.RAp != BUTTON_OFF) {
				Button_Status.RAp = BUTTON_OFF;	
				Button_Status.RAp_Change = 1;
			}		
		} else {
			//Button Off for the first time...
			Button_Status_TMP.RAp = BUTTON_OFF;
		}
	} else {
		//Button On
		if(Button_Status_TMP.RAp == BUTTON_ON) {
			//Button Off for the second time...
			if(Button_Status.RAp != BUTTON_ON) {
				Button_Status.RAp = BUTTON_ON;
				Button_Status.RAp_Change = 1;
			}				
		} else {
			//Button Off for the first time...
			Button_Status_TMP.RAp = BUTTON_ON;
		}	
	}	
	
	//RA- (low-active)
	if( PINC & (1<<PINC2) ) {
		//Button Off
		if(Button_Status_TMP.RAm == BUTTON_OFF) {
			//Button Off for the second time...
			if(Button_Status.RAm != BUTTON_OFF) {
				Button_Status.RAm = BUTTON_OFF;	
				Button_Status.RAm_Change = 1;
			}			
		} else {
			//Button Off for the first time...
			Button_Status_TMP.RAm = BUTTON_OFF;
		}
	} else {
		//Button On
		if(Button_Status_TMP.RAm == BUTTON_ON) {
			//Button Off for the second time...
			if(Button_Status.RAm != BUTTON_ON) {
				Button_Status.RAm = BUTTON_ON;	
				Button_Status.RAm_Change = 1;
			}
		} else {
			//Button Off for the first time...
			Button_Status_TMP.RAm = BUTTON_ON;
		}	
	}	
	
	//DEC+ (low-active)
	if( PINC & (1<<PINC5) ) {
		//Button Off
		if(Button_Status_TMP.DECp == BUTTON_OFF) {
			//Button Off for the second time...
			if(Button_Status.DECp != BUTTON_OFF) {
				Button_Status.DECp = BUTTON_OFF;
				Button_Status.DECp_Change = 1;
			}				
		} else {
			//Button Off for the first time...
			Button_Status_TMP.DECp = BUTTON_OFF;
		}
	} else {
		//Button On
		if(Button_Status_TMP.DECp == BUTTON_ON) {
			//Button Off for the second time...
			if(Button_Status.DECp != BUTTON_ON) {
				Button_Status.DECp = BUTTON_ON;
				Button_Status.DECp_Change = 1;
			}				
		} else {
			//Button Off for the first time...
			Button_Status_TMP.DECp = BUTTON_ON;
		}	
	}	
	
	
	//DEC- (low-active)
	if( PINC & (1<<PINC4) ) {
		//Button Off
		if(Button_Status_TMP.DECm == BUTTON_OFF) {
			//Button Off for the second time...
			if(Button_Status.DECm != BUTTON_OFF) {
				Button_Status.DECm = BUTTON_OFF;
				Button_Status.DECm_Change = 1;
			}				
		} else {
			//Button Off for the first time...
			Button_Status_TMP.DECm = BUTTON_OFF;
		}
	} else {
		//Button On
		if(Button_Status_TMP.DECm == BUTTON_ON) {
			//Button Off for the second time...
			if(Button_Status.DECm != BUTTON_ON) {
				Button_Status.DECm = BUTTON_ON;
				Button_Status.DECm_Change = 1;
			}				
		} else {
			//Button Off for the first time...
			Button_Status_TMP.DECm = BUTTON_ON;
		}	
	}		


	return;	
}

void Button_CheckForAction(void) {
	
	static struct {
		uint8_t RAp_Active;
		uint8_t RAm_Active;
		uint8_t DECp_Active;
		uint8_t DECm_Active;		
	} Action_State = {0, 0, 0, 0};
	
	if(!Action_State.RAm_Active && Button_Status.RAp_Change) {
		if(Button_Status.RAp == BUTTON_ON) {	
			//RA+ pressed, RA- not active
				
			Action_State.RAp_Active = 1;
			Button_Status.RAp_Change = 0;
			
			Action_RApButtonPressed();
		}
		else if(Button_Status.RAp == BUTTON_OFF) {
			//RA+ unpressed, RA- not active
			
			Action_RApButtonUnpressed();
			
			Action_State.RAp_Active = 0;
			Button_Status.RAp_Change = 0;
		}
	}
		
	if(!Action_State.RAp_Active && Button_Status.RAm_Change) {
		if(Button_Status.RAm == BUTTON_ON) {	
			//RA- pressed, RA+ not active
				
			Action_State.RAm_Active = 1;
			Button_Status.RAm_Change = 0;
			
			Action_RAmButtonPressed();
		}
		else if(Button_Status.RAm == BUTTON_OFF) {
			//RA- unpressed, RA+ not active
			
			Action_RAmButtonUnpressed();
			
			Action_State.RAm_Active = 0;
			Button_Status.RAm_Change = 0;	
		}			
	}	
	
	
	if(!Action_State.DECm_Active && Button_Status.DECp_Change) {
		if(Button_Status.DECp == BUTTON_ON) {	
			//DEC+ pressed, DEC- not active
				
			Action_State.DECp_Active = 1;
			Button_Status.DECp_Change = 0;
			
			Action_DECpButtonPressed();
		}
		else if(Button_Status.DECp == BUTTON_OFF) {
			//DEC+ unpressed, DEC- not active
			
			Action_DECpButtonUnpressed();
			
			Action_State.DECp_Active = 0;
			Button_Status.DECp_Change = 0;
		}
	}
		
	if(!Action_State.DECp_Active && Button_Status.DECm_Change) {
		if(Button_Status.DECm == BUTTON_ON) {	
			//DEC- pressed, DEC+ not active
				
			Action_State.DECm_Active = 1;
			Button_Status.DECm_Change = 0;
			Action_DECmButtonPressed();
		}
		else if(Button_Status.DECm == BUTTON_OFF) {
			//DEC- unpressed, DEC+ not active
			Action_DECmButtonUnpressed();
			
			Action_State.DECm_Active = 0;
			Button_Status.DECm_Change = 0;	
		}			
	}	
}