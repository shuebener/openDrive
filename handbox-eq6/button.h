/*
 * button.h
 *
 * Created: 12.05.2011 15:37:57
 *  Author: Huebener.Se
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTTON_ON 1
#define BUTTON_OFF 0

typedef struct {
	uint8_t RAp;			//0 = Off; 1 = On
	uint8_t RAp_Change;		//
	uint8_t RAm;			//0 = Off; 1 = On
	uint8_t RAm_Change;		//
	uint8_t DECp;			//0 = Off; 1 = On
	uint8_t DECp_Change;	//
	uint8_t DECm;			//0 = Off; 1 = On
	uint8_t DECm_Change;	//
} BUTTON_STATUS_t;
#define BUTTON_STATUS_DEFAULT {BUTTON_OFF, 0, BUTTON_OFF, 0, BUTTON_OFF, 0, BUTTON_OFF, 0}

void Button_Update(void);
void Button_CheckForAction(void) ;


#endif /* BUTTON_H_ */