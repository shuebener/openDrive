/*
 * action.h
 *
 * Created: 13.05.2011 13:23:06
 *  Author: Huebener.Se
 */ 


#ifndef ACTION_H_
#define ACTION_H_


void Action_RApButtonPressed(void);
void Action_RApButtonUnpressed(void);
void Action_RAmButtonPressed(void);
void Action_RAmButtonUnpressed(void);
void Action_DECpButtonPressed(void);
void Action_DECpButtonUnpressed(void);
void Action_DECmButtonPressed(void);
void Action_DECmButtonUnpressed(void);

void SendCmd(char CMD[21], char Value[6]);
void getSpeed(uint8_t SS_Speed, char Speed[]);


#endif /* ACTION_H_ */