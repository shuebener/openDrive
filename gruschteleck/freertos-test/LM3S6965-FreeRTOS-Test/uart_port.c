#include "debug.h"

#include "lm3s_cmsis.h"
#include "LM3S6965_Bitdef.h"

#include "FreeRTOS.h"
#include "task.h"

#include "uart_port.h"


extern uint32_t SysP_SystemFrequency;



void UARTPort_Init(void) {

	uint32_t baudDivInt, baudDivFrac, oBaudrate, rBaudrate;

	oBaudrate = 2000000;

    UART0->CTL

    baudDivInt = SysP_SystemFrequency / (16 * oBaudrate);
    baudDivFrac = SysP_SystemFrequency % (16 * oBaudrate);
    baudDivFrac = ((((baudDivFrac * 8) / oBaudrate) + 1) / 2);

    //rBaudrate = (SysP_SystemFrequency * 4) / ((64 * baudDivInt) + baudDivFrac);
	//float Error = 100.0 - 100.0 / (float)(oBaudrate) * (float)(rBaudrate);
	//debug_printf("%d => %d,%d => %d [%.2f%%]\n", oBaudrate, baudDivInt, baudDivFrac, rBaudrate, Error);


	UART0->IBRD = (baudDivInt << UARTn_IBRD_DIVINT);
    UART0->FBRD	= (baudDivFrac << UARTn_FBRD_DIVFRAC);

}