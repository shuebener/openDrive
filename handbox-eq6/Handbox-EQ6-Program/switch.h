/*
 * switch.h
 *
 * Created: 12.05.2011 11:19:04
 *  Author: Huebener.Se
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#define SWITCH_SS_SPEED_2X		0
#define SWITCH_SS_SPEED_8X		1
#define SWITCH_SS_SPEED_16X		2
#define SWITCH_SS_HEM_N			0
#define SWITCH_SS_HEM_S			1
#define SWITCH_SS_REVRA_OFF		0
#define SWITCH_SS_REVRA_ON		1
#define SWITCH_SS_REVDEC_OFF	0
#define SWITCH_SS_REVDEC_ON		1

typedef struct {
	uint8_t Speed;			//0 = 2x; 1 = 8x; 2 = 16x
	uint8_t Hemisphere;		//0 = North; 1 = South
	uint8_t Reverse_Ra;		//0 = Off; 1 = On
	uint8_t Reverse_Dec;	//0 = Off; 1 = On
} SWITCH_STATUS_t;
#define SWITCH_STATUS_DEFAULT {SWITCH_SS_SPEED_2X, SWITCH_SS_HEM_N, SWITCH_SS_REVRA_OFF, SWITCH_SS_REVDEC_OFF}

void Switch_Update();


#endif /* SWITCH_H_ */